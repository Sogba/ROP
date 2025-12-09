#include "sfml.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics.hpp>

sf::Font font("src/fonts/digital7.ttf");

sf::RenderWindow initialWindowSettings(){
  sf::ContextSettings context;
  sf::Font font("src/fonts/digital7.ttf");
  context.antiAliasingLevel = 8;

  return sf::RenderWindow (sf::VideoMode({640, 360}), "ROP", sf::Style::Default, sf::State::Windowed, context);
}

sf::Text defaultText(){
  sf::Text text(font);

  text.setCharacterSize(48);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Regular);

  return text;
}

void handleWindowResize(sf::Vector2u size, sf::RenderWindow &window){
  sf::View view = window.getDefaultView();
  view.setSize(static_cast<sf::Vector2f>(size));

  view.setCenter({
    view.getSize().x/2,
    view.getSize().y/2
  });
  window.setView(view);
}