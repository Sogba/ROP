#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "qol/qol.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include "sfml/sfml.h"
#include <iostream>


int main(int argc, char* argv[]){
	message::start();
	std::cout << "\n" << argc << "\n";

	int currentSyncMode = getCurrentSynchronizationMode(argc, argv);
	
	sf::Text clock1Text = defaultText();


	clk::clock clock1 = clk::nowClockValues();
	
	if(argc > 2)
		clock1 = clk::zeroClockValues();

	
	clk::clock renderClock;
	sf::RenderWindow window = initialWindowSettings();

	if(currentSyncMode == syncMethod::NO)
		clock1.makeErrors = true;

	bool threadsShouldRun = true;

	clk::setupClocks({&clock1});
	std::thread clockIncrementation(threadIncrementingClock, &clock1, &threadsShouldRun, currentSyncMode);
	while(window.isOpen()){

		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (event->is<sf::Event::Resized>())
				handleWindowResize(event->getIf<sf::Event::Resized>()->size, window);
		}

		if(resolveSync(&clock1, currentSyncMode, &renderClock))
			clock1Text.setString(clk::clockToString(&renderClock));
		window.clear(sf::Color::Black);
		window.draw(clock1Text);
		window.display();

		clock1Text.setOrigin({clock1Text.getLocalBounds().size.x / 2.0f, clock1Text.getLocalBounds().size.y});
		clock1Text.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});
		clock1Text.setCharacterSize(window.getSize().y / 5 * 2);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	threadsShouldRun = false;
	clockIncrementation.join();

	message::end();
}