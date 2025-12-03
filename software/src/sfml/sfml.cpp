#include "sfml.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics.hpp>

sf::RenderWindow initialWindowSettings(){
  sf::ContextSettings context;
  sf::Font font("src/fonts/digital7.ttf");
  context.antiAliasingLevel = 8;

  return sf::RenderWindow (sf::VideoMode({800, 600}), "ROP", sf::Style::Default, sf::State::Windowed, context);
}
