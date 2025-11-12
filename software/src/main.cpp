#include <iostream>
#include <SFML/Graphics.hpp>

class FPS
{ 
public:
	FPS() : mFrame(0), mFps(0) {}
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update()
	{
		if(mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}

		++mFrame;
	}
};

int main(){
	std::cout << "ROP started\n";
  FPS fps;
	sf::ContextSettings context;
	context.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({800, 600}), "ROP", sf::Style::Default, sf::State::Windowed, context);

	sf::CircleShape triangle(90.f, 3);

	while(window.isOpen()){
		while (const std::optional event = window.pollEvent()){
			if (event->is<sf::Event::Closed>())
					window.close();
		}

		window.clear(sf::Color::Black);

		window.draw(triangle);

		window.display();


		fps.update();
		std::cout << "FPS:" << fps.getFPS() << "\r";	
	}

	std::cout << "ROP ended\n";
}