#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include "../qol/qol.h"
sf::Text defaultText();


class clockText {
private:
  short positionIndex;

  short error;

  sf::Text hours = defaultText();
  sf::Text minutes = defaultText();
  sf::Text seconds = defaultText();

  sf::RenderWindow* window;
  clk::clock* clock;

public:
  sf::Text divider1 = defaultText();
  sf::Text divider2 = defaultText();

  clockText(sf::RenderWindow* window, clk::clock* clock, short positionIndex);

  void resize();
  void draw();
  void updateText();
};

sf::RenderWindow initialWindowSettings();
void handleWindowResize(sf::Vector2u size, sf::RenderWindow* window, clockText* clockText1, clockText* clockText2);

