﻿#include <SFML/Graphics.hpp>
#include "Engine.hpp"


template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &v)
{
	out << "{ " << v.x << ", " << v.y << " }";
	return out;
}

namespace parametrs
{
	nlohmann::json info = load_infof();
	auto default_resolution = sf::Vector2u(info["Resolution"][0], info["Resolution"][1]);
	bool vsync = info["Vsync"];
	unsigned int frame_limit = info["Framerate-limit"];
	int window_mode = info["Window-mode"] ? sf::Style::Default : sf::Style::Fullscreen;
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
	using Vec2f = sf::Vector2f;
	using engine::math::mix;
	using namespace parametrs;
	using Rect = sf::RectangleShape;
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(default_resolution.x, default_resolution.y, mode.bitsPerPixel), "Card Wars", window_mode);
	window.setFramerateLimit(frame_limit);
	window.setVerticalSyncEnabled(vsync);
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
	Button start = Button(bsize, "Start", font, (uint32_t)abs(floor(engine::math::length(res))) / 54u);
	Button settings = Button(bsize, "Settings", font, (uint32_t)abs(floor(engine::math::length(res))) / 54u);
	Button about_us = Button(bsize, "About Us", font, (uint32_t)abs(floor(engine::math::length(res))) / 54u);
	Button exit = Button(bsize, "Exit", font, (uint32_t)abs(floor(engine::math::length(res))) / 54u);
	std::vector<Button> buttons; // buttons too
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
					b.setSize(bsize);
					b.setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
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
				b.setColor(mix(bcolor, sf::Color::White));
			else b.setColor(bcolor);
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
	sf::Mouse m;
	Vector2f mpos;
	Vector2u ures = window.getSize();
	Vector2f res = Vector2f(ures);
	std::vector<Vector2u> resolutions = { {800, 600}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}, {2560, 1440} };
	std::vector<uint16_t> framerates = { 30, 59, 60, 75, 100, 120, 144, 240, 360 };
	Vector2f bpos = Vector2f(res.x / 3.f, res.y / 8.f); // button position
	Vector2f bsize = Vector2f(res.x / 9.6f, res.y / 18.f); // button size
	Vector2f bsize2 = Vector2f(res.x / 4.8f, res.y / 18.f); // screen buttons size
	Vector2f swsize = Vector2f(res.x / 32.f, res.y / 18.f); // switcher size
	sf::Color bcolor = sf::Color(115, 1, 4); // button color (reddish for me plz)
	auto &font = loadFont();
	// buttons
	Button backB = Button(bsize, "Back", font, ures.y / 27u); // save
	Button resetB = Button(bsize, "Reset", font, ures.y / 27u); // reset
	Button saveB = Button(Vector2f(bsize), "Save", font, ures.y / 27u);
	Button switcherL = Button(swsize, "<", font, ures.y / 27u); // left resolution switcher 
	Button switcherR = Button(swsize, ">", font, ures.y / 27u); // right resolution switcher
	std::string ressx = std::to_string(window.getSize().x); // string resolution x
	std::string ressy = std::to_string(window.getSize().y); // string resolution y
	Button rScreen = Button(bsize2, ressx+" x "+ressy, font, ures.y / 27u); // resolution display through button
	Button switcherWMode = Button(swsize, window_mode == sf::Style::Default ? "" : "+", font, ures.y / 27u); // window mode switcher
	Button switcherVsync = Button(swsize, vsync == true ? "+" : "", font, ures.y / 27u); // vsync mode switcher
	std::string frp = std::to_string(frame_limit); // string frame limit
	Button switcherLF = Button(swsize, "<", font, ures.y / 27u); // switchers for framerate
	Button switcherRF = Button(swsize, ">", font, ures.y / 27u);
	Button fScreen = Button(bsize2, frp, font, ures.y / 27u); // framerate display through button

	enum Buttons
	{
		Back = 1, Save = 2, Reset = 3,
		LeftResolutionSwitcher = 4, ResolutionViewer = 5, RightResolutionSwitcher = 6,
		LeftFramerateSwicher = 7, FramerateViewer = 8, RightFramerateSwitcher = 9,
		VideoModeSwitcher = 10, VsyncSwitcher = 11
	};

	std::vector<Button> buttons;
	buttons.push_back(backB);	      // 1
	buttons.push_back(saveB);         // 2
	buttons.push_back(resetB);        // 3
	buttons.push_back(switcherL);     // 4
	buttons.push_back(rScreen);       // 5
	buttons.push_back(switcherR);     // 6
	buttons.push_back(switcherLF);    // 7
	buttons.push_back(fScreen);       // 8
	buttons.push_back(switcherRF);    // 9
	buttons.push_back(switcherWMode); // 10
	buttons.push_back(switcherVsync); // 11
	float w;
	nlohmann::json jsf = load_infof();
	uint8_t i, j, n, k;
	size_t p1 = 4ull; // p1 - resulution id
	size_t p2 = 2ull; // p2 - framerate id
	unsigned int rx = 1920, ry = 1080, video_mode = sf::Style::Default;
	uint16_t fr = 60;
	bool vsy = true, wmode = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::Resized: // if screen was resized
				sf::FloatRect varea = sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(varea));
				res = Vector2f(window.getSize());
				bpos = Vector2f(res.x / 3.f, res.y / 8.f); // button position
				bsize = Vector2f(res.x / 9.6f, res.y / 18.f); // button size
				bsize2 = Vector2f(res.x / 4.8f, res.y / 18.f); // screen buttons size
				swsize = Vector2f(res.x / 32.f, res.y / 18.f); // switcher size
				buttons[0].setSize(bsize); // back
				buttons[1].setSize(bsize); // save
				buttons[2].setSize(bsize); // reset
				buttons[3].setSize(swsize); // switcher l
				buttons[4].setSize(bsize2); // rtarget
				buttons[5].setSize(swsize); // switcher r
				buttons[6].setSize(swsize); // fswitcher l
				buttons[7].setSize(bsize2); // ftarget
				buttons[8].setSize(swsize); // fswitcher r
				buttons[9].setSize(swsize); // switcher wmode
				buttons[10].setSize(swsize); // switcher vsync
				for (auto &b : buttons)
					b.setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
			}
		}
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		//code
		k = 1, j = i = 0, w = 0.f;
		for (auto &b : buttons)
		{
			if (b.isIntersected(mpos) && k != ResolutionViewer && k != FramerateViewer)
				b.setColor(mix(bcolor, sf::Color::White));
			else b.setColor(bcolor);

			//button positioning
			if (k == Back)
                b.setPosition(Vector2f(0, 0));

			else if (k == Save or k == Reset)
				b.setPosition(Vector2f(res.x, (++i) * res.y / 10) - b.getSize());
			else
			{
				n = static_cast<uint8_t>(abs(floor(j / 3.f)));
				w = j % 3 == 0 ? 0 : w + buttons[k-2].getSize().x;
				b.setPosition(Vector2f(bpos.x + w + (j % 3)*res.x/27.f, bpos.y + n*bsize.y + 100));
				j++;
			}
            if (b.isPressed(sf::Mouse::Button::Left, mpos))
			{
                // button functions
				switch (k)
				{
				case Back:
					return;
				case Save:
					rx = resolutions[p1].x;
					ry = resolutions[p1].y;
					fr = framerates[p2];
					resetInfoResolution(rx, ry);
					resetInfoVsync(vsy);
					resetInfoFramerateLimit(fr);
					resetInfoWindowMode(wmode);
					window.close();
					wmode ? sf::Style::Default : sf::Style::Fullscreen;
					window.create(sf::VideoMode(window.getSize().x, window.getSize().y, sf::VideoMode::getDesktopMode().bitsPerPixel), "Card Wars", video_mode);
					window.setSize(Vector2u(rx, ry));
					window.setVerticalSyncEnabled(vsy);
					window.setFramerateLimit(fr);
					break;
				case Reset:
					create_infof();
					break;
				case LeftResolutionSwitcher:
					p1 = std::max(p1 - 1, 0ull); // limit
					buttons[4].setString(std::to_string(resolutions[p1].x) + " x " + std::to_string(resolutions[p1].y));
					break;
				case ResolutionViewer:
					buttons[4].setString(":P");
					break;
				case RightResolutionSwitcher:
					p1 = std::min(p1 + 1, resolutions.size() - 1); // limit
					buttons[4].setString(std::to_string(resolutions[p1].x) + " x " + std::to_string(resolutions[p1].y));
					break;
				case LeftFramerateSwicher:
					p2 = std::max(p2 - 1, 0ull); // limit
					buttons[7].setString(std::to_string(framerates[p2]));
					break;
				case FramerateViewer:
					buttons[7].setString(":D");
					break;
				case RightFramerateSwitcher: 
					p2 = std::min(p2 + 1, framerates.size() - 1); // limit
					buttons[7].setString(std::to_string(framerates[p2]));
					break;
				case VideoModeSwitcher:
					wmode = !wmode;
					if (wmode) b.setString("+");
					else if (!wmode) b.setString("");
					break;
				case VsyncSwitcher:
					vsy = !vsy;
					if (vsy) b.setString("+");
					else if (!vsy) b.setString("");
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
	using Vec2f = sf::Vector2f;
	using engine::math::mix;
	using namespace engine::cards;
	using namespace parametrs;
	WitherSkeleton ws(window.getSize());
	ws.setPosition(Vec2f(window.getSize())/2.f);
	ws.setOrigin(ws.getSize()/2.f);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		window.clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;
		window.draw(ws);
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
	Button back(bsize, "Back", font, ures.y / 27u);
	Vector2f bpos = Vector2f(0, 0);
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
				bpos = Vector2f(0, res.y - back.getSize().y);
				bsize = Vector2f(res.x / 9.6f, res.y / 18.f);
				back.setPosition(bpos);
				back.setSize(bsize);
				back.setCharacterSize((uint64_t)abs(floor(engine::math::length(res))) / 54u);
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
			back.setColor(mix(bcolor, sf::Color::White));
		else back.setColor(bcolor);
		if (back.isPressed(sf::Mouse::Button::Left, mpos))
			return;
		window.draw(rect);
		window.draw(text);
		window.draw(back);
		window.draw(cardlol);
		window.display();
	}
}
