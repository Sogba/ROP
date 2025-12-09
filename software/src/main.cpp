#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "terminalOutput.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "sfml/sfml.h"

int main(){
	message::start();
	sf::Text hodiny1 = defaultText();
	
	int h1 = 0;
	int m1 = 0;

	sf::RenderWindow window = initialWindowSettings();

	while(window.isOpen()){
		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (event->is<sf::Event::Resized>())
				handleWindowResize(event->getIf<sf::Event::Resized>()->size, window);
		}
		
		m1++;
		if(m1 >= 60){
			m1 = 0;
			h1++;
		}
		if(h1 >= 24)
			h1 = 0;

		hodiny1.setString(std::to_string(h1) + ":" + std::to_string(m1));
		window.clear(sf::Color::Black);
		window.draw(hodiny1);
		window.display();
	}

	message::end();
}