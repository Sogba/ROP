#include "qol/qol.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <string>
#include <thread>
#include "sfml/sfml.h"

int main(int argc, char* argv[]){
	message::start();

	int currentSyncMode = getCurrentSynchronizationMode(argc, argv);
	
	clk::clock clock1 = clk::nowClockValues();
	clk::clock clock2 = clk::nowClockValues();
	clk::clock renderClock;

	clk::setupClocks({&clock1, &clock2});
	clock1.makeErrors = true;
	if(argc > 2){
		clock1 = clk::zeroClockValues();
		clock2 = clk::zeroClockValues();
	}	

	bool threadsShouldRun = true;
	bool showImGui = false;

	float speedQ = 1;

	static std::string currentSyncModeString;

	switch (currentSyncMode) {
		case syncMethod::ATOMIC : currentSyncModeString = "ATOMIC"; break;
		case syncMethod::MUTEX : currentSyncModeString = "MUTEX"; break;
		case syncMethod::SEMAPHORE : currentSyncModeString = "SEMAPHORE"; break;
		case syncMethod::NO : currentSyncModeString = "NO SYNC"; break;
	}

	sf::Window window = initialWindowSettings();

	std::thread clockIncrementation1(threadIncrementingClock, &clock1, &threadsShouldRun, syncMethod::NO);
	std::thread clockIncrementation2(threadIncrementingClock, &clock2, &threadsShouldRun, currentSyncMode);

	while(window.isOpen()){

		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (event->is<sf::Event::Resized>());
				//handleWindowResize(event->getIf<sf::Event::Resized>()->size, window);
				//Do something after the window is resized
		}

		if(resolveSync(&clock1, syncMethod::NO, &renderClock));
			//Set text of clock1 after logic resolve

		if(resolveSync(&clock2, currentSyncMode, &renderClock));
			//Set text of clock2 after logic resolve
	}

	threadsShouldRun = false;
	clockIncrementation1.join();
	clockIncrementation2.join();

	message::end();
}