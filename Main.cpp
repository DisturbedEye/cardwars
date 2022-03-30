#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.hpp"


int main()
{
	using engine::math::mix;
	using sf::Vector2f;
	const unsigned int screen_width = 1920, screen_height = 1080; // temprary
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height, mode.bitsPerPixel), "Card Wars");
	window.setFramerateLimit(60);
	float time;
	sf::Mouse mouse;
	Vector2f bpos = Vector2f(screen_width, screen_height) / 2.f;
	Vector2f bsize = Vector2f(300.f, 100.f);
	Vector2f bhalfsize = bsize / 2.f;
	engine::Button<sf::RectangleShape> button = engine::Button<sf::RectangleShape>(sf::RectangleShape(bsize));
	sf::Font font;
	if (!font.loadFromFile("Fonts\\Winston\\Winston-Regular.ttf"))
	{
		std::cout << "FileNotFoundError: File \"Winston-Regular.ttf\" not found!";
		throw;
	}
	button.content.setFont(font);
	button.content.setCharacterSize(60);
	sf::Color bcolor = sf::Color(115, 101, 174);
	button.setOrigin(bhalfsize);
	button.setPosition(bpos);
	button.shape.setFillColor(bcolor);
	Vector2f mpos;
	bool before, after;
	before = mouse.isButtonPressed(sf::Mouse::Button::Left);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
		window.clear(); // clears screen
		// code
		mpos = Vector2f(mouse.getPosition(window));
		after = mouse.isButtonPressed(sf::Mouse::Button::Left);
		button.waitForAction(before, after, mpos);
		before = mouse.isButtonPressed(sf::Mouse::Button::Left);
		if (button.isIntersected())
			button.shape.setFillColor(mix(bcolor, sf::Color::White));
		else button.shape.setFillColor(bcolor);
		if (button.isHold())
			button.content.setString("WHAT?!");
		else button.content.setString("NO?!");
		button.content.setPosition(Vector2f(bpos.x + bhalfsize.x/4.f, bpos.y));
		window.draw(button);
		window.display();
	}
}
