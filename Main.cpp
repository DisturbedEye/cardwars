#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.hpp"

std::ostream &operator<<(std::ostream &out, const sf::Vector2f &v)
{
	out << "{ " << v.x << ", " << v.y << " }";
	return out;
}

namespace parametrs
{
	sf::Vector2u resolution = sf::Vector2u(1920u, 1080u);
	sf::Vector2f resolutionf = sf::Vector2f(1920.f, 1080.f);
	uint8_t frame_limit = 60;
}
sf::Font &loadFont()
{
	static sf::Font font;
	if (!font.loadFromFile("Fonts\\RezaZulmiSerif\\RezaZulmiSerif.ttf"))
	{
		std::cout << "FileNotFoundError: File \"Winston-Regular.ttf\" not found!";
		throw;
	}
	return font;
}
void start_game(sf::RenderWindow &window);
void game_settings(sf::RenderWindow &window);
int main_menu(sf::RenderWindow &window);
void about_us(sf::RenderWindow &window);

int main()
{
	using engine::Button;
	using sf::Vector2f;
	using engine::math::mix;
	using namespace parametrs;
	typedef sf::RectangleShape Rect;
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y, mode.bitsPerPixel), "Card Wars");
	window.setFramerateLimit(60);
	int position = 0; // 0 - main menu, 1 - start game, 2 - in settings, 3 about us? 4 - exit
	while (position != 4)
	{
		position = main_menu(window);
		if (position == 1)
			start_game(window);
		else if (position == 2)
			game_settings(window);
		else if (position == 3)
			about_us(window);
	}
	return 0;
}

int main_menu(sf::RenderWindow &window)
{
	using engine::Button;
	using sf::Vector2f;
	using engine::math::mix;
	using namespace parametrs;
	typedef sf::RectangleShape Rect;
	Vector2f res = Vector2f(resolutionf.x, resolutionf.y);
	sf::Mouse mouse;
	Vector2f bpos = Vector2f(res.x / 6, res.y) / 2.f; // button position
	Vector2f bsize = Vector2f(200.f, 60.f); // button size
	Vector2f bhalfsize = bsize / 2.f; // half of button size
	// buttons 

	Button<Rect> start = engine::Button<Rect>(Rect(bsize));
	Button<Rect> settings = engine::Button<Rect>(Rect(bsize));
	Button<Rect> about_us = engine::Button<Rect>(Rect(bsize));
	Button<Rect> exit = engine::Button<Rect>(Rect(bsize));

	std::vector<engine::Button<sf::RectangleShape>> buttons; // buttons too 
	sf::Font &font = loadFont();
	start.content = sf::Text("Start", font, resolution.y / 27u);

	settings.content = sf::Text("Settings", font, resolution.y / 27u);

	about_us.content = sf::Text("About Us", font, resolution.y / 27u);

	exit.content = sf::Text("Exit", font, resolution.y / 27u);

	buttons.push_back(start); // 1
	buttons.push_back(settings); // 2
	buttons.push_back(about_us); // 3
	buttons.push_back(exit); // 4
	sf::Color bcolor = sf::Color(115, 101, 174); // button color
	for (auto &i : buttons)
		i.shape.setOrigin(bhalfsize);
	Vector2f mpos;
	bool before = mouse.isButtonPressed(sf::Mouse::Button::Left), after;
	int j, k;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		window.clear(); // clears screen
		// code
		mpos = Vector2f(mouse.getPosition(window));
		k = 1;
		j = 0;
		after = mouse.isButtonPressed(sf::Mouse::Button::Left); // no
		for (auto &b : buttons)
		{
			if (b.isIntersected(mpos))
				b.shape.setFillColor(mix(bcolor, sf::Color::White));
			else b.shape.setFillColor(bcolor);

			if (b.isPressed(before, after, mpos))
				return k;
			b.setPosition(Vector2f(bpos.x + bhalfsize.x / 4.f, bpos.y + (j++) * res.y / 12 + bhalfsize.y));
			window.draw(b);
			k++;
		}
		before = mouse.isButtonPressed(sf::Mouse::Button::Left); // don't touch
		window.display();
	}
}


void game_settings(sf::RenderWindow &window)
{
	/*
	* settings
	* screen resolution
	* frame limit
	* audio (later add)
	* other settings
	*/
	using engine::Button;
	using sf::Vector2f;
	using engine::math::mix;
	using namespace parametrs;
	typedef sf::RectangleShape Rect;
	Vector2f ssize = Vector2f(60, 60); // switchers size
	Vector2f tsize = Vector2f(400, 60); // rtarget size
	Button<Rect> switcherL = Button<Rect>(Rect(ssize));
	Button<Rect> switcherR = Button<Rect>(Rect(ssize));
	Button<Rect> rscreen = Button<Rect>(Rect(tsize));
	auto &font = loadFont();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		window.clear();
		window.display();
	}
}

void start_game(sf::RenderWindow &window)
{
	using engine::Button;
	using sf::Vector2f;
	using engine::math::mix;
	using namespace parametrs;
	typedef sf::RectangleShape Rect;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		window.clear();
		window.display();
	}
}

void about_us(sf::RenderWindow &window)
{
	using engine::Button;
	using sf::Vector2f;
	using engine::math::mix;
	using namespace parametrs;
	typedef sf::RectangleShape Rect;
	Button<Rect> back(Rect(Vector2f(resolutionf.x/9.6f, resolutionf.y/18.f)));
	Vector2f bpos = Vector2f( 0, resolutionf.y - back.shape.getSize().y );
	sf::Mouse m;
	Rect rect(Vector2f(resolutionf.x * 2.f / 3.f, resolutionf.y));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setPosition(resolutionf.x / 2.f, resolutionf.y / 2.f);
	rect.setFillColor(sf::Color(67, 67, 67));
	sf::Texture texture;
	texture.loadFromFile("images\\evolution.jpg");
	sf::Sprite cardlol;
	cardlol.setScale(0.5f, 0.5f);
	cardlol.setTexture(texture);
	cardlol.setPosition(rect.getPosition().x, resolutionf.y/3.f);
	cardlol.setOrigin(cardlol.getGlobalBounds().width, 0);
	sf::Color bcolor = sf::Color(115, 101, 174); // button color
	sf::Font &font = loadFont();
	back.content = sf::Text("Back", font, resolution.y/27u);
	back.content.setOrigin(-back.content.getGlobalBounds().width/2.f, 0.f);
	sf::Text text("About Us:", font, resolution.y / 27u);
	text.setPosition(resolution.x/2.f - text.getGlobalBounds().width /2.f, 0.f);
	back.setPosition(bpos);
	Vector2f mpos;
	bool before = m.isButtonPressed(sf::Mouse::Button::Left), after;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		after = m.isButtonPressed(sf::Mouse::Button::Left); // don't touch this
		if (back.isIntersected(mpos))
			back.shape.setFillColor(mix(bcolor, sf::Color::White));
		else back.shape.setFillColor(bcolor);
		if (back.isPressed(before, after, mpos))
			return;
		before = m.isButtonPressed(sf::Mouse::Button::Left); // don't touch this
		window.draw(rect);
		window.draw(text);
		window.draw(back);
		window.draw(cardlol);
		window.display();
	}
}
