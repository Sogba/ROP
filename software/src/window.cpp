#include "window.h"
#include <SFML/Graphics.hpp>

sf::RenderWindow initialWindowSettings(){
  sf::ContextSettings context;

  context.antiAliasingLevel = 16;

  return sf::RenderWindow (sf::VideoMode({800, 600}), "ROP", sf::Style::Default, sf::State::Windowed, context);
}
