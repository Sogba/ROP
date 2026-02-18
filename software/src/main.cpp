#include "qol/qol.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
#include <string>
#include <thread>
#include "sfml/sfml.h"

int main(int argc, char* argv[]){
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
	if(argc > 2){
		clock1 = clk::zeroClockValues();
		clock2 = clk::zeroClockValues();
	}	

	bool threadsShouldRun = true;
	

	static std::string currentSyncModeString;

	switch (currentSyncMode) {
		case syncMethod::ATOMIC : currentSyncModeString = "ATOMIC"; break;
		case syncMethod::MUTEX : currentSyncModeString = "MUTEX"; break;
		case syncMethod::SEMAPHORE : currentSyncModeString = "SEMAPHORE"; break;
		case syncMethod::NO : currentSyncModeString = "NO SYNC"; break;
	}

	clockText clockText1(&window, &renderClock, 1);
	clockText clockText2(&window, &renderClock, 3);

	sf::Text modeText = defaultText();
	modeText.setString(currentSyncModeString);
	sf::Text speedText = defaultText();
	
	sfmlInit(&window, &clockText1, &clockText2, &modeText, &speedText, &speedQ);

	std::thread clockIncrementation1(threadIncrementingClock, &clock1, &threadsShouldRun, syncMethod::NO);
	std::thread clockIncrementation2(threadIncrementingClock, &clock2, &threadsShouldRun, currentSyncMode);

	setSpeedText();
	handleWindowResize({640, 360});
	while(window.isOpen()){

		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (event->is<sf::Event::Resized>())
				handleWindowResize(event->getIf<sf::Event::Resized>()->size);
			
		}

		if(resolveSync(&clock1, syncMethod::NO, &renderClock))
			clockText1.updateText();

		if(resolveSync(&clock2, currentSyncMode, &renderClock))
			clockText2.updateText();
	

		window.clear(sf::Color::Black);
		clockText1.draw();
		clockText2.draw();
		window.draw(modeText);
		window.draw(speedText);
		window.display();
	}

	threadsShouldRun = false;
	clockIncrementation1.join();
	clockIncrementation2.join();

	message::end();
}