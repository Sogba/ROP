#include "sfml.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include "../qol/d7.hpp"


namespace{
  sf::Font font;

  void correctWindowSize(sf::RenderWindow* window, sf::Text inputText){
    sf::Vector2u windowNewSize = window->getSize();

    windowNewSize.x = static_cast<int>(inputText.getLocalBounds().size.y)*10 + static_cast<int>(inputText.getLetterSpacing())*3;

    if(inputText.getCharacterSize()%12!=0)
      windowNewSize.y = windowNewSize.y + (12 - (inputText.getCharacterSize() % 12)) * 3;

    window->setSize(windowNewSize);
  }

  sf::Text syncModeText = defaultText();
  sf::Text speedQText = defaultText();
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

  correctWindowSize(window, clockText1->divider1);
}

clockText::clockText(sf::RenderWindow* window, clk::clock* clock, short positionIndex){
  clockText::window = window;
  clockText::clock = clock;
  
  clockText::positionIndex = positionIndex;
  clockText::error = 0;

  clockText::divider1.setString(":");
  clockText::divider2.setString(":");

  clockText::updateText();
  clockText::resize();
} 

void clockText::resize(){
  unsigned int characterSize = clockText::window->getSize().y / 3;

  clockText::hours.setCharacterSize(characterSize);
  clockText::divider1.setCharacterSize(characterSize);
  clockText::minutes.setCharacterSize(characterSize);
  clockText::divider2.setCharacterSize(characterSize);
  clockText::seconds.setCharacterSize(characterSize);

  clockText::hours.setPosition({(window->getSize().x / 2.0f) - clockText::hours.getLocalBounds().size.x * 2, clockText::hours.getLocalBounds().size.y*1.5f*static_cast<float>(clockText::positionIndex)});
  sf::Vector2f hoursPosition = clockText::hours.getPosition();
  sf::Vector2f hoursSize = clockText::hours.getLocalBounds().size;

  clockText::divider1.setPosition({hoursPosition.x + hoursSize.x, hoursPosition.y});
  clockText::minutes.setPosition({hoursPosition.x + hoursSize.x/2*3, hoursPosition.y});
  clockText::divider2.setPosition({hoursPosition.x + hoursSize.x/2*5, hoursPosition.y});
  clockText::seconds.setPosition({hoursPosition.x + hoursSize.x*3, hoursPosition.y});
}

void clockText::draw(){
  clockText::window->draw(hours);
  clockText::window->draw(divider1);
  clockText::window->draw(minutes);
  clockText::window->draw(divider2);
  clockText::window->draw(seconds);
}

void clockText::updateText(){
  clockText::hours.setString(std::format("{:02}", clockText::clock->hours));
  clockText::minutes.setString(std::format("{:02}", clockText::clock->minutes));
  clockText::seconds.setString(std::format("{:02}", clockText::clock->seconds));

  if(clockText::error){
    hours.setFillColor(sf::Color::White);
    minutes.setFillColor(sf::Color::White);
    seconds.setFillColor(sf::Color::White); 

    clockText::error = false;
  }


  if(clockText::clock->hours > 23){
    clockText::hours.setFillColor(sf::Color::Red);
    clockText::error = true;
  }
  if(clockText::clock->minutes > 59){
    clockText::minutes.setFillColor(sf::Color::Red);
    clockText::error = true;
  }
  if(clockText::clock->seconds > 59){
    clockText::seconds.setFillColor(sf::Color::Red);
    clockText::error = true;
  }
}


