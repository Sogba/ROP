#include "qol/qol.h"
#include "sfml/sfml.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
#include <imgui-SFML.h>
#include <imgui_internal.h>
#include <iostream>
#include <string>
#include <thread>

void restartClocks(clk::clock &clock1, clk::clock &clock2, float speed,
                   int syncMode, bool &threadsShouldRun, std::thread &t1,
                   std::thread &t2) {
  // Stop old threads
  threadsShouldRun = false;

  if (t1.joinable())
    t1.join();
  if (t2.joinable())
    t2.join();

  // Reset clocks to NOW
  clock1 = clk::nowClockValues();
  clock2 = clk::nowClockValues();

  // Apply new speed
  clk::setupClocks({&clock1, &clock2}, speed);

  threadsShouldRun = true;

  // Restart threads with new sync mode
  t1 = std::thread(threadIncrementingClock, &clock1, &threadsShouldRun,
                   syncMethod::NO);

  t2 = std::thread(threadIncrementingClock, &clock2, &threadsShouldRun,
                   syncMode);
}

int main(int argc, char *argv[]) {
  message::start();

  sf::RenderWindow window = initialWindowSettings();
  window.setFramerateLimit(144);

  bool showImGui = false;

  int currentSyncMode = getCurrentSynchronizationMode(argc, argv);

  clk::clock clock1 = clk::nowClockValues();
  clk::clock clock2 = clk::nowClockValues();
  clk::clock renderClock = clk::zeroClockValues();

  float speedQ = 4;

  clk::setupClocks({&clock1, &clock2}, speedQ);
  clock1.makeErrors = true;
  if (argc > 2) {
    clock1 = clk::zeroClockValues();
    clock2 = clk::zeroClockValues();
  }

  bool threadsShouldRun = true;

  static std::string currentSyncModeString;

  switch (currentSyncMode) {
  case syncMethod::ATOMIC:
    currentSyncModeString = "ATOMIC";
    break;
  case syncMethod::MUTEX:
    currentSyncModeString = "MUTEX";
    break;
  case syncMethod::SEMAPHORE:
    currentSyncModeString = "SEMAPHORE";
    break;
  case syncMethod::NO:
    currentSyncModeString = "NO SYNC";
    break;
  }

  clockText clockText1(&window, &renderClock, 1);
  clockText clockText2(&window, &renderClock, 3);

  sf::Text modeText = defaultText();
  modeText.setString(currentSyncModeString);
  sf::Text speedText = defaultText();

  sfmlInit(&window, &clockText1, &clockText2, &modeText, &speedText, &speedQ);
  ImGui::SFML::Init(window);

  std::thread clockIncrementation1(threadIncrementingClock, &clock1,
                                   &threadsShouldRun, syncMethod::NO);
  std::thread clockIncrementation2(threadIncrementingClock, &clock2,
                                   &threadsShouldRun, currentSyncMode);

  setSpeedText();
  handleWindowResize({640, 360});
  sf::Clock deltaClock;
  while (window.isOpen()) {

    while (const std::optional event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);
      if (event->is<sf::Event::Closed>())
        window.close();
      else if (event->is<sf::Event::Resized>())
        handleWindowResize(event->getIf<sf::Event::Resized>()->size);
      else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::S)
          showImGui = !showImGui;
      }
    }

    if (resolveSync(&clock1, syncMethod::NO, &renderClock))
      clockText1.updateText();

    if (resolveSync(&clock2, currentSyncMode, &renderClock))
      clockText2.updateText();

if (showImGui)
{
    ImGui::SFML::Update(window, deltaClock.restart());
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("FullscreenWindow", nullptr, flags);

    ImGui::SetWindowFontScale(1.5f);

    // --------------------------------------------------
    // CENTERING BLOCK
    // --------------------------------------------------

    float windowWidth  = ImGui::GetWindowWidth();
    float windowHeight = ImGui::GetWindowHeight();

    float blockWidth = 400.f;   // width of our UI block
    float blockStartX = (windowWidth - blockWidth) * 0.5f;

    ImGui::SetCursorPosY(windowHeight * 0.3f);
    ImGui::SetCursorPosX(blockStartX);

    ImGui::BeginGroup();
    ImGui::PushItemWidth(blockWidth);

    ImGui::Text("Clock Settings");
    ImGui::Separator();
    ImGui::Spacing();

    // --------------------------------------------------
    // SPEED CONTROL
    // --------------------------------------------------

    ImGui::DragFloat(
        "Speed",
        &speedQ,
        0.1f,
        1.0f,
        10.0f,
        "%.1f"
    );

    ImGui::Spacing();
    ImGui::Spacing();

    // --------------------------------------------------
    // SYNC MODE RADIO BUTTONS
    // --------------------------------------------------

    ImGui::Text("Synchronization Mode");
    ImGui::Separator();

    ImGui::RadioButton("ATOMIC",     &currentSyncMode, syncMethod::ATOMIC);
    ImGui::RadioButton("MUTEX",      &currentSyncMode, syncMethod::MUTEX);
    ImGui::RadioButton("SEMAPHORE",  &currentSyncMode, syncMethod::SEMAPHORE);

    ImGui::Spacing();
    ImGui::Spacing();

    // --------------------------------------------------
    // RESTART BUTTON
    // --------------------------------------------------

    if (ImGui::Button("Restart From Now", ImVec2(blockWidth, 0)))
    {
        restartClocks(
            clock1,
            clock2,
            speedQ,
            currentSyncMode,
            threadsShouldRun,
            clockIncrementation1,
            clockIncrementation2
        );

        setSpeedText();
        modeText.setString(
            currentSyncMode == syncMethod::NO        ? "NO SYNC" :
            currentSyncMode == syncMethod::ATOMIC    ? "ATOMIC" :
            currentSyncMode == syncMethod::MUTEX     ? "MUTEX" :
                                                       "SEMAPHORE"
        );
    }

    ImGui::PopItemWidth();
    ImGui::EndGroup();

    ImGui::End();
}
else
{
    deltaClock.restart();
}

    window.clear(sf::Color::Black);
    clockText1.draw();
    clockText2.draw();
    window.draw(modeText);
    window.draw(speedText);
    if (showImGui)
      ImGui::SFML::Render(window);
    window.display();
  }

  threadsShouldRun = false;
  clockIncrementation1.join();
  clockIncrementation2.join();

  message::end();
}