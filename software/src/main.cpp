#include "terminalOutput.h"
#include <SFML/Graphics.hpp>
#include "sfml/sfml.h"


int main(){

	message::start();

	

	sf::RenderWindow window = initialWindowSettings();
	window.setFramerateLimit(300);

	sf::Clock deltaClock;
	while(window.isOpen()){
		while (const std::optional event = window.pollEvent()){

			if (event->is<sf::Event::Closed>())
					window.close();
		}

	window.clear(sf::Color::Black);
	window.display();
	}

	message::end();
}