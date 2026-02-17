#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <ostream>
#include "../qol/d7.hpp"
#include "sfml.h"
#include <iostream>


namespace{
  sf::Font font;

  void correctWindowSize(sf::RenderWindow* window, clockText someClockText){
    sf::Vector2u windowNewSize = window->getSize();

    window->setSize(windowNewSize);
  }
}


sf::RenderWindow initialWindowSettings(){
  sf::ContextSettings context;

  context.antiAliasingLevel = 8;
  return sf::RenderWindow (sf::VideoMode({640, 360}), "ROP", sf::Style::Default, sf::State::Windowed, context);
}

sf::Text defaultText(){
  font.openFromMemory(MyFont_ttf, MyFont_ttf_len);
  sf::Text text(font);
  text.setCharacterSize(100);
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Regular);

  return text;
}

void handleWindowResize(sf::Vector2u size, sf::RenderWindow* window, clockText* clockText1, clockText* clockText2){
  sf::View view = window->getDefaultView();
  view.setSize(static_cast<sf::Vector2f>(size));
  view.setCenter({
    view.getSize().x/2,
    view.getSize().y/2
  });
  window->setView(view);
  
  clockText1->resize();
  clockText2->resize();

  //correctWindowSize(window, clockText1->divider1);
}

clockText::clockText(sf::RenderWindow* window, clk::clock* clock, short positionIndex){
  clockText::window = window;
  clockText::clock = clock;
  
  clockText::positionIndex = positionIndex;
  error = 0;

  divider1.setString(":");
  divider2.setString(":");


  updateText();
  resize();
} 

void clockText::resize()
{
    float characterSize = window->getSize().y / 3.f;

    hours.setCharacterSize(std::round(characterSize));
    divider1.setCharacterSize(std::round(characterSize));
    minutes.setCharacterSize(std::round(characterSize));
    divider2.setCharacterSize(std::round(characterSize));
    seconds.setCharacterSize(std::round(characterSize));

    auto centerOrigin = [](sf::Text& text)
    {
        auto b = text.getLocalBounds();
        text.setOrigin({
            b.position.x + b.size.x * 0.5f,
            b.position.y + b.size.y * 0.5f
        });
    };

    centerOrigin(hours);
    centerOrigin(divider1);
    centerOrigin(minutes);
    centerOrigin(divider2);
    centerOrigin(seconds);

    float y = window->getSize().y / 6.f * (positionIndex * 2 - 1);

  float spacing = characterSize * 0.1f;

  float totalWidth =
      hours.getLocalBounds().size.x +
      divider1.getLocalBounds().size.x +
      minutes.getLocalBounds().size.x +
      divider2.getLocalBounds().size.x +
      seconds.getLocalBounds().size.x +
      spacing * 4.f;   // 4 gaps between 5 elements

  float startX = window->getSize().x / 2.f - totalWidth / 2.f;
  float x = startX;

  hours.setPosition({x + hours.getLocalBounds().size.x / 2.f, y});
  x += hours.getLocalBounds().size.x + spacing;

  divider1.setPosition({x + divider1.getLocalBounds().size.x / 2.f, y});
  x += divider1.getLocalBounds().size.x + spacing;

  minutes.setPosition({x + minutes.getLocalBounds().size.x / 2.f, y});
  x += minutes.getLocalBounds().size.x + spacing;

  divider2.setPosition({x + divider2.getLocalBounds().size.x / 2.f, y});
  x += divider2.getLocalBounds().size.x + spacing;

  seconds.setPosition({x + seconds.getLocalBounds().size.x / 2.f, y});
}

void clockText::draw(){
  window->draw(hours);
  window->draw(divider1);
  window->draw(minutes);
  window->draw(divider2);
  window->draw(seconds);
}

void clockText::updateText(){
  hours.setString(std::format("{:02}", clock->hours));
  minutes.setString(std::format("{:02}", clock->minutes));
  seconds.setString(std::format("{:02}", clock->seconds));

  if(error){
    hours.setFillColor(sf::Color::White);
    minutes.setFillColor(sf::Color::White);
    seconds.setFillColor(sf::Color::White); 

    error = false;
  }


  if(clock->hours > 23){
    hours.setFillColor(sf::Color::Red);
    error = true;
  }
  if(clock->minutes > 59){
    minutes.setFillColor(sf::Color::Red);
    error = true;
  }
  if(clock->seconds > 59){
    seconds.setFillColor(sf::Color::Red);
    error = true;
  }
}


