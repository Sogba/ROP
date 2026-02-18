#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <utility>
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
  float totalWidth();
  std::pair<float, float> horizontalBounds();
};

sf::RenderWindow initialWindowSettings();
void handleWindowResize(sf::Vector2u size);
void sfmlInit(sf::RenderWindow *inputWindow, clockText *inputClockText1, clockText *inputClockText2, sf::Text *inputModeText, sf::Text *inputSpeedText, float *inputSpeedQ);
void setSpeedText();