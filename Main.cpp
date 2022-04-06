#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.hpp"
#include <string>
template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &v)
{
	out << "{ " << v.x << ", " << v.y << " }";
	return out;
}

namespace parametrs
{
	sf::Vector2u default_resolution = sf::Vector2u(1920u, 1080u);
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
	sf::RenderWindow window(sf::VideoMode(default_resolution.x, default_resolution.y, mode.bitsPerPixel), "Card Wars");
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
	sf::Vector2u ures = window.getSize();
	Vector2f res = Vector2f(ures);
	sf::Mouse mouse;
	Vector2f bpos = Vector2f(res.x / 6, res.y) / 2.f; // button position
	Vector2f bsize = Vector2f(res.x / 9.6f, res.y / 18.f); // button size
	Vector2f bhalfsize = bsize / 2.f; // half of button size
	sf::Font &font = loadFont();
	// buttons
	Button<Rect> start = engine::Button<Rect>(Rect(bsize), "Start", font, ures.y / 27u);
	Button<Rect> settings = engine::Button<Rect>(Rect(bsize), "Settings", font, ures.y / 27u);
	Button<Rect> about_us = engine::Button<Rect>(Rect(bsize), "About Us", font, ures.y / 27u);
	Button<Rect> exit = engine::Button<Rect>(Rect(bsize), "Exit", font, ures.y / 27u);
	std::vector<engine::Button<sf::RectangleShape>> buttons; // buttons too
	buttons.push_back(start);	 // 1
	buttons.push_back(settings); // 2
	buttons.push_back(about_us); // 3
	buttons.push_back(exit);	 // 4
	sf::Color bcolor = sf::Color(115, 101, 174); // button color
	Vector2f mpos;
	uint8_t k;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::Resized:
				sf::FloatRect varea(0, 0, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(varea));
				res = Vector2f(window.getSize());
				bpos = Vector2f(res.x / 6, res.y) / 2.f;
				bsize = Vector2f(res.x / 9.6f, res.y / 18.f);
				for (auto &b : buttons)
				{
					b.shape.setSize(bsize);
					b.content.setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
					b.resetToCenter();
				}
			}
		}
		window.clear(); // clears screen
		// code
		mpos = Vector2f(mouse.getPosition(window));
		k = 1;
		for (auto &b : buttons)
		{
			if (b.isIntersected(mpos))
				b.shape.setFillColor(mix(bcolor, sf::Color::White));
			else b.shape.setFillColor(bcolor);
			if (b.isPressed(sf::Mouse::Button::Left, mpos))
				return k;
			b.setPosition(Vector2f(bpos.x, bpos.y + (k - 1) * (res.y/24.f + bsize.y)));
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
	using sf::Vector2f, sf::Vector2u;
	using std::min, std::max;
	using engine::math::mix;
	using namespace parametrs;
	typedef sf::RectangleShape Rect;
	sf::Mouse m;
	Vector2f mpos;
	Vector2u ures = window.getSize();
	Vector2f res = Vector2f(ures);
	std::vector<Vector2u> resolutions = { {2560, 1440}, {1920, 1080}, {1600, 900}, {1366, 768}, {1280, 720}, {800, 600} };

	Vector2f bpos = Vector2f(res.x / 3.f, res.y / 8.f); // button position
	Vector2f bsize = Vector2f(res.x / 9.6f, res.y / 18.f); // button size
	sf::Color bcolor = sf::Color(115, 1, 4); // button color (reddish for me plz)
	auto &font = loadFont();

	// buttons
	Button<Rect> backB = Button<Rect>(Rect(bsize), "Back", font, ures.y / 27u);
	Button<Rect> resetB = Button<Rect>(Rect(bsize), "Reset", font, ures.y / 27u);
	Button<Rect> saveB = Button<Rect>(Rect(Vector2f(bsize)), "Save", font, ures.y / 27u);
	Button<Rect> switcherL = Button<Rect>(Rect(Vector2f(res.x / 32.f, res.y / 18.f)), "<", font, ures.y / 27u);
	Button<Rect> switcherR = Button<Rect>(Rect(Vector2f(res.x / 32.f, res.y / 18.f)), ">", font, ures.y / 27u);
	std::string ressx = std::to_string(default_resolution.x);
	std::string ressy = std::to_string(default_resolution.y);
	Button<Rect> rScreen = Button<Rect>(Rect(Vector2f(res.x / 4.8f, res.y / 18.f)), ressx+" x "+ressy, font, ures.y / 27u); // resolution display through button

	//totally not ripped off from main menu surely
	std::vector<engine::Button<sf::RectangleShape>> buttons;
	buttons.push_back(backB);	  // 1
	buttons.push_back(switcherL); // 2
	buttons.push_back(rScreen);   // 3
	buttons.push_back(switcherR); // 4
	buttons.push_back(saveB);     // 5
	buttons.push_back(resetB);    // 6
	for (int i = 1; i <= 3; i++)
		std::cout << floor(i / 3) << "\n";
    uint8_t i, j, k, n;
	float w;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

			case sf::Event::Resized:
				sf::FloatRect varea(0, 0, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(varea));
				res = Vector2f(window.getSize());
				bpos = Vector2f(res.x / 6.f, res.y / 3.f) / 2.f; // button position
				bsize = Vector2f(res.x / 9.6f, res.y / 18.f); // button size
				buttons[0].shape.setSize(Vector2f(res.x / 9.6f, res.y / 18.f)); // back
				buttons[1].shape.setSize(Vector2f(res.x / 4.8f, res.y / 18.f)); // switcher l
				buttons[2].shape.setSize(Vector2f(res.x / 4.8f, res.y / 18.f)); // rtarget
				buttons[3].shape.setSize(Vector2f(res.x / 4.8f, res.y / 18.f)); // switcher r
				buttons[4].shape.setSize(Vector2f(res.x / 9.6f, res.y / 18.f)); // save
				buttons[5].shape.setSize(Vector2f(res.x / 5.5f, res.y / 18.f)); // reset
				for (auto &b : buttons)
				{
					b.content.setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
					b.resetToCenter();
				}
			}
		}
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		//code
		k = 1, j = i = w = 0;
		for (auto &b : buttons) 
		{
			if (b.isIntersected(mpos) && k != 3)
				b.shape.setFillColor(mix(bcolor, sf::Color::White));
			else b.shape.setFillColor(bcolor);
			//button positioning

			if (k == 1) // back
                b.setPosition(Vector2f(0, 0));

			else if (k == buttons.size() or k == buttons.size() - 1)
				b.setPosition(Vector2f(res.x, (++i) * res.y / 10) - b.shape.getSize());

			else 
			{
				n = floor(j / 3.f);
				w = j % 3 == 0 ? 0 : w + buttons[k-2].shape.getSize().x;
				b.setPosition(Vector2f(bpos.x + w + (j % 3)*res.x/27.f, bpos.y + n*bsize.y));
				j++;
			}
            if (b.isPressed(sf::Mouse::Button::Left, mpos))
			{
                // button functions
                switch (k)
				{
                // back
                case 1: 
					return;
				// settings
				case 2: // left slider 
					break;
				case 3: // resolution "viewer"
					break;
				case 4: // right slider
					break;
				// save
				case 5:
					break;
				// reset
				case 6:
					break;
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
	sf::Vector2u ures = window.getSize();
	Vector2f res = Vector2f(ures);
	Vector2f bsize = Vector2f(res.x / 9.6f, res.y / 18.f);
	Button<Rect> back(Rect(bsize), "Back", font, ures.y / 27u);
	Vector2f bpos = Vector2f( 0, res.y - back.shape.getSize().y );
	sf::Mouse m;
	Rect rect = Rect(Vector2f(res.x * 2.f / 3.f, res.y));
	rect.setOrigin(rect.getSize() / 2.f);
	rect.setPosition(res.x / 2.f, res.y / 2.f);
	rect.setFillColor(sf::Color(67, 67, 67));
	sf::Texture texture;
	texture.loadFromFile("images\\evolution.jpg");
	sf::Sprite cardlol;
	cardlol.setScale(0.5f, 0.5f);
	cardlol.setTexture(texture);
	cardlol.setPosition(rect.getPosition().x, res.y/3.f);
	cardlol.setOrigin(cardlol.getGlobalBounds().width, 0);
	sf::Color bcolor = sf::Color(115, 101, 174); // button color
	sf::Text text("About Us:", font, ures.y / 27u);
	text.setPosition(res.x/2.f - text.getGlobalBounds().width /2.f, 0.f);
	back.setPosition(bpos); // setting back button pos
	Vector2f mpos;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::Resized:
				Vector2f *bres = new Vector2f(res); // before resolution
				sf::FloatRect varea(0, 0, (float) event.size.width, (float) event.size.height);
				window.setView(sf::View(varea));
				res = Vector2f(window.getSize());
				bpos = Vector2f(0, res.y - back.shape.getSize().y);
				bsize = Vector2f(res.x / 9.6f, res.y / 18.f);
				back.setPosition(bpos);
				back.shape.setSize(bsize);
				back.content.setCharacterSize((uint64_t)abs(floor(engine::math::length(res))) / 54u);
				back.resetToCenter();
				rect.setSize(Vector2f(res.x * 2.f / 3.f, res.y));
				rect.setOrigin(rect.getSize() / 2.f);
				rect.setPosition(res.x / 2.f, res.y / 2.f);
				cardlol.setScale(0.5f * res.x / bres->x, 0.5f * res.y / bres->y);
				delete bres;
				cardlol.setPosition(rect.getPosition().x, res.y / 3.f);
				cardlol.setOrigin(cardlol.getGlobalBounds().width, 0);
				text.setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
				text.setPosition(res.x / 2.f - text.getGlobalBounds().width / 2.f, 0.f);
			}
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
