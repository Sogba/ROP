#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "qol/qol.h"
#include <SFML/Graphics.hpp>
#include "sfml/sfml.h"

int main(){
	message::start();
	sf::Text clock1Text = defaultText();

	clk::clock clock1 = clk::zeroClockValues();
	sf::RenderWindow window = initialWindowSettings();

	clk::setupClocks({&clock1});	
	while(window.isOpen()){

		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (event->is<sf::Event::Resized>())
				handleWindowResize(event->getIf<sf::Event::Resized>()->size, window);
		}
		clk::clockIncrement(&clock1);
		clock1Text.setString(clk::clockToString(&clock1));
		window.clear(sf::Color::Black);
		window.draw(clock1Text);
		window.display();
	}

	message::end();
}