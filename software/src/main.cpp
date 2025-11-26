#include "terminalOutput.h"
#include <SFML/Graphics.hpp>
#include "window.h"
#include "jobs.h"
#include <iostream>

int main(){

	message::start();

    // Dummy synchronization functions
    auto syncStart = []() {
        std::cout << "Sync start called\n";
    };

    auto syncEnd = []() {
        std::cout << "Sync end called\n";
    };

    // Run the transcribe function (from previous vector version)
    transcribe(syncStart, syncEnd);

/* 	sf::RenderWindow window = initialWindowSettings();
	sf::CircleShape triangle(90.f, 3);

	while(window.isOpen()){
		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())
					window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(triangle);
		window.display();
	}
 */
	message::end();
}