#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.hpp"
#include <string>

std::ostream &operator<<(std::ostream &out, const sf::Vector2f &v)
{
	out << "{ " << v.x << ", " << v.y << " }";
	return out;
}

namespace parametrs
{
	sf::Vector2u resolution = sf::Vector2u(1920u, 1080u);
	uint8_t frame_limit = 60u;
}
sf::Font &loadFont()
{
	static sf::Font font;
	if (!font.loadFromFile("Fonts\\RezaZulmiSerif\\RezaZulmiSerif.ttf"))
	{
		std::cout << "FileNotFoundError: File \"RezaZulmiSerif.ttf\" not found!";
		throw;
	}
	return font;
}
void start_game(sf::RenderWindow &window);
void game_settings(sf::RenderWindow &window);
int main_menu(sf::RenderWindow &window);
void about_us(sf::RenderWindow &window);

void draw_card(sf::RenderWindow &window)
{
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
	Vector2f res = Vector2f(float(resolution.x), float(resolution.y));
	sf::Mouse mouse;
	Vector2f bpos = Vector2f(res.x / 6, res.y) / 2.f; // button position
	Vector2f bsize = Vector2f(200.f, 60.f); // button size
	Vector2f bhalfsize = bsize / 2.f; // half of button size
	sf::Font &font = loadFont();
	// buttons
	Button<Rect> start = engine::Button<Rect>(Rect(bsize), "Start", font, resolution.y / 27u);
	Button<Rect> settings = engine::Button<Rect>(Rect(bsize), "Settings", font, resolution.y / 27u);
	Button<Rect> about_us = engine::Button<Rect>(Rect(bsize), "About Us", font, resolution.y / 27u);
	Button<Rect> exit = engine::Button<Rect>(Rect(bsize), "Exit", font, resolution.y / 27u);
	std::vector<engine::Button<sf::RectangleShape>> buttons; // buttons too
	buttons.push_back(start);	 // 1
	buttons.push_back(settings); // 2
	buttons.push_back(about_us); // 3
	buttons.push_back(exit);	 // 4
	sf::Color bcolor = sf::Color(115, 101, 174); // button color
	Vector2f mpos;
	uint8_t j, k;
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
		for (auto &b : buttons)
		{
			if (b.isIntersected(mpos))
				b.shape.setFillColor(mix(bcolor, sf::Color::White));
			else b.shape.setFillColor(bcolor);
			if (b.isPressed(sf::Mouse::Button::Left, mpos))
				return k;
			b.setPosition(Vector2f(bpos.x, (bpos.y + (j++) * (float(resolution.y)/24.f+bsize.y))));
			window.draw(b);
			k++;
		}
		window.display();
	}
	return 0;
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
	sf::Mouse m;
	Vector2f mpos;
	Vector2f res = Vector2f(float(resolution.x), float(resolution.y));
	std::vector<Vector2f> resolutions = { {2560, 1440}, {1920, 1080}, {1600, 900}, {1366, 768}, {1280, 720}, {800, 600} };

	Vector2f bpos = Vector2f(res.x / 6, res.y /3) / 2.f; // button position
	Vector2f ssize = Vector2f(60.f, 60.f); // switchers size
	Vector2f tsize = Vector2f(400.f, 60.f); // rtarget size
	Vector2f bsize = Vector2f(200.f, 60.f); // button size
	Vector2f rsize = Vector2f(350.f, 60.f); // reset button size
	Vector2f bhalfsize = bsize / 2.f; // half of button size
	sf::Color bcolor = sf::Color(115, 1, 4); // button color (reddish for me plz)
	auto &font = loadFont();

	// buttons
	Button<Rect> backB = Button<Rect>(Rect(bsize), "Back", font, resolution.y / 27u);
	Button<Rect> resetB = Button<Rect>(Rect(bsize), "Save", font, resolution.y / 27u);
	Button<Rect> saveB = Button<Rect>(Rect(rsize), "Reset to defaults", font, resolution.y / 27u);
	Button<Rect> switcherL = Button<Rect>(Rect(ssize), "<", font, resolution.y / 27u);
	Button<Rect> switcherR = Button<Rect>(Rect(ssize), ">", font, resolution.y / 27u);
	std::string ressx;
	std::string ressy;
	ressx = std::to_string(resolution.x);
	ressy = std::to_string(resolution.y);
	Button<Rect> rScreen = Button<Rect>(Rect(tsize), ressx+" x "+ressy, font, resolution.y / 27u); // resolution display through button


	//totally not ripped off from main menu surely
	std::vector<engine::Button<sf::RectangleShape>> buttons;
	buttons.push_back(backB);	  // 1
	buttons.push_back(saveB);     // 2
	buttons.push_back(resetB);    // 3
	buttons.push_back(switcherL); // 4
	buttons.push_back(rScreen);   // 5
	buttons.push_back(switcherR); // 6

    uint8_t j, k;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		//code
		k = 1;
		j = 0;
		for (auto &b : buttons){
            if (b.isIntersected(mpos) && k!=5)
                b.shape.setFillColor(mix(bcolor, sf::Color::White));
            else b.shape.setFillColor(bcolor);
            //button positioning
            if (k == 1){
                b.setPosition(Vector2f(0, 0));
            }
            if (k >= 4 && k <=6){
                b.setPosition(Vector2f((bpos.x + (j++) * (float(resolution.y)/24.f+ssize.x)), bpos.y));
                if (k == 6){
                    b.setPosition(Vector2f((bpos.x + (j++) * (float(resolution.y)/24.f+ssize.x)+tsize.x/1.75), bpos.y));
                }
            }
            if (k >=2 && k < 4){
                b.setPosition(Vector2f((bpos.x + (j++) * (float(resolution.y)/24.f+rsize.x)), res.y-bpos.y));
            }
            if (b.isPressed(sf::Mouse::Button::Left, mpos)){
                // button functions
                switch (k){
                    // back
                    case 1: return;
                    // save
                    case 2:{

                    }
                    // reset
                    case 3:{

                    }
                    // etc
                    case 4:{

                    }
                    case 6:{

                    }
                }
            }
            k++;
            window.draw(b);
		}
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;
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
	sf::Font &font = loadFont();
	Button<Rect> back(Rect(Vector2f(float(resolution.x)/9.6f, float(resolution.y)/18.f)), "Back", font, resolution.y / 27u);
	Vector2f bpos = Vector2f( 0, float(resolution.y) - back.shape.getSize().y );
	sf::Mouse m;
	Rect rect(Vector2f(float(resolution.x) * 2.f / 3.f, float(resolution.y)));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setPosition(float(resolution.x) / 2.f, float(resolution.y) / 2.f);
	rect.setFillColor(sf::Color(67, 67, 67));
	sf::Texture texture;
	texture.loadFromFile("images\\evolution.jpg");
	sf::Sprite cardlol;
	cardlol.setScale(0.5f, 0.5f);
	cardlol.setTexture(texture);
	cardlol.setPosition(rect.getPosition().x, float(resolution.y)/3.f);
	cardlol.setOrigin(cardlol.getGlobalBounds().width, 0);
	sf::Color bcolor = sf::Color(115, 101, 174); // button color
	sf::Text text("About Us:", font, resolution.y / 27u);
	text.setPosition(resolution.x/2.f - text.getGlobalBounds().width /2.f, 0.f);
	back.setPosition(bpos);
	Vector2f mpos;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		//code
		if (back.isIntersected(mpos))
			back.shape.setFillColor(mix(bcolor, sf::Color::White));
		else back.shape.setFillColor(bcolor);
		if (back.isPressed(sf::Mouse::Button::Left, mpos))
			return;
		window.draw(rect);
		window.draw(text);
		window.draw(back);
		window.draw(cardlol);
		window.display();
	}
}
