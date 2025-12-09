#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Window.hpp"
#include <SFML/Graphics.hpp>

sf::RenderWindow initialWindowSettings();
sf::Text defaultText();
void handleWindowResize(sf::Vector2u size, sf::RenderWindow &window);