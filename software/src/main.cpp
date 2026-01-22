#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "qol/qol.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include "sfml/sfml.h"
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>

int main(int argc, char* argv[]){
	message::start();

	int currentSyncMode = getCurrentSynchronizationMode(argc, argv);
	
	sf::Text clock1Text = defaultText();
	sf::Text clock2Text = defaultText();
	sf::Text syncModeText = defaultText();
	sf::Text speedText = defaultText();

	clk::clock clock1 = clk::nowClockValues();
	clk::clock clock2 = clk::nowClockValues();
	
	if(argc > 2){
		clock1 = clk::zeroClockValues();
		clock2 = clk::zeroClockValues();
	}	

	clk::clock renderClock;
	sf::RenderWindow window = initialWindowSettings();

	clock1.makeErrors = true;

	bool threadsShouldRun = true;

	clk::setupClocks({&clock1, &clock2});

	std::thread clockIncrementation1(threadIncrementingClock, &clock1, &threadsShouldRun, syncMethod::NO);
	std::thread clockIncrementation2(threadIncrementingClock, &clock2, &threadsShouldRun, currentSyncMode);

	static std::string currentSyncModeString;
	float speedQ = 1;

	switch (currentSyncMode) {
		case syncMethod::ATOMIC : currentSyncModeString = "ATOMIC"; break;
		case syncMethod::MUTEX : currentSyncModeString = "MUTEX"; break;
		case syncMethod::SEMAPHORE : currentSyncModeString = "SEMAPHORE"; break;
		case syncMethod::NO : currentSyncModeString = "NO SYNC"; break;
	}

	syncModeText.setString(currentSyncModeString);

bool showImGui = false;

window.setFramerateLimit(144);

if (!ImGui::SFML::Init(window))
        return -1;

sf::Clock clock;

	while(window.isOpen()){

		while (const std::optional event = window.pollEvent()){
			ImGui::SFML::ProcessEvent(window, *event);
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (event->is<sf::Event::Resized>())
				handleWindowResize(event->getIf<sf::Event::Resized>()->size, window);
		}

		if(resolveSync(&clock1, syncMethod::NO, &renderClock))
			clock1Text.setString(clk::clockToString(&renderClock));

		if(resolveSync(&clock2, currentSyncMode, &renderClock))
			clock2Text.setString(clk::clockToString(&renderClock));

		speedText.setString(std::format("{:.2f}", speedQ) + "X");

		clock1Text.setOrigin({clock1Text.getLocalBounds().size.x / 2.0f, clock1Text.getLocalBounds().size.y});
		clock1Text.setPosition({window.getSize().x / 2.0f, window.getSize().y / 4.0f});
		clock1Text.setCharacterSize(window.getSize().y / 5 * 2);

		clock2Text.setOrigin({clock1Text.getLocalBounds().size.x / 2.0f, clock2Text.getLocalBounds().size.y});
		clock2Text.setPosition({window.getSize().x / 2.0f, window.getSize().y / 4.0f * 3});
		clock2Text.setCharacterSize(window.getSize().y / 5 * 2);

		syncModeText.setOrigin({syncModeText.getLocalBounds().size.x / 2.0f, syncModeText.getLocalBounds().size.y});
		syncModeText.setPosition({(clock1Text.getPosition().x*1.0f - 0.5f*clock1Text.getLocalBounds().size.x + 0.5f*syncModeText.getLocalBounds().size.x), window.getSize().y / 4.0f * 2});
		syncModeText.setCharacterSize(window.getSize().y / 5);

		speedText.setOrigin({syncModeText.getLocalBounds().size.x / 2.0f, syncModeText.getLocalBounds().size.y});
		speedText.setPosition({(clock1Text.getPosition().x*1.0f + 0.5f*clock1Text.getLocalBounds().size.x - 0.5f*speedText.getLocalBounds().size.x), window.getSize().y / 4.0f * 2});
		speedText.setCharacterSize(window.getSize().y / 5);

	ImGui::SFML::Update(window, clock.restart());

		ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();


		window.clear(sf::Color::Black);
		if(showImGui)
			ImGui::SFML::Render(window);		
		window.draw(clock1Text);
		window.draw(clock2Text); 
		window.draw(syncModeText);
		window.draw(speedText);
		window.display();

		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	ImGui::SFML::Shutdown();
	threadsShouldRun = false;
	clockIncrementation1.join();
	clockIncrementation2.join();

	message::end();
}