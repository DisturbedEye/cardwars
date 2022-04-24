#include <SFML/Graphics.hpp>
#include "Engine.hpp"


template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &v)
{
	out << "{ " << v.x << ", " << v.y << " }";
	return out;
}

namespace parametrs
{
	sf::Vector2u default_resolution = engine::getInfoResolution();
	bool vsync = engine::getInfoVsync();
	unsigned int frame_limit = engine::getInfoFramerateLimit();
	int window_mode = engine::getInfoVideoMode();
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
	using Vec2u = sf::Vector2u;
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
	sf::Texture bttex;
	sf::Texture bctex;
	if (bttex.loadFromFile("images\\button.png") && bctex.loadFromFile("images\\menu.png")){
        bttex.setSmooth(true);
        bctex.setSmooth(true);
	}
	sf::RectangleShape r = sf::RectangleShape();
	r.setSize(Vector2f(res.x, res.y));
	r.setTexture(&bctex);
	// buttons
	Button start = Button(bsize, "Start", font, (uint32_t)abs(floor(engine::math::length(res))) / 64u);
	Button settings = Button(bsize, "Settings", font, (uint32_t)abs(floor(engine::math::length(res))) / 64u);
	Button about_us = Button(bsize, "About Us", font, (uint32_t)abs(floor(engine::math::length(res))) / 64u);
	Button exit = Button(bsize, "Exit", font, (uint32_t)abs(floor(engine::math::length(res))) / 64u);
	std::vector<Button> buttons; // buttons too
	buttons.push_back(start);	 // 1
	buttons.push_back(settings); // 2
	buttons.push_back(about_us); // 3
	buttons.push_back(exit);	 // 4
	sf::Color bcolor = sf::Color(200, 200, 200); // button color
	Vector2f mpos;
	uint8_t k;
	sf::Text txt("Rune Wars", font);
	txt.setPosition(res.x / 6, res.y / 4);
	Vec2u bres = window.getSize();
    txt.setScale(txt.getScale().x * 1.5f, txt.getScale().y * 1.5f);

	while (window.isOpen())
	{
		float time = engine::math::time(); // current time after starting program
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				sf::FloatRect varea(0, 0, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(varea));
				res = Vector2f(window.getSize());
				bpos = Vector2f(res.x / 6, res.y) / 2.f;
				bsize = Vector2f(res.x / 9.6f, res.y / 18.f);
				for (auto &b : buttons)
				{
					b.setSize(bsize);
					b.setScale(Vector2f(res.x / bres.x, res.y / bres.y));
				}
				txt.setScale(res.x / bres.x, res.y/bres.y);
				r.setSize(Vector2f(res.x / bres.x, res.y / bres.y));
			}
		}
		window.clear(); // clears screen
		// code
		mpos = Vector2f(mouse.getPosition(window));
		window.draw(r);
		k = 1;
		for (auto &b : buttons)
		{
		    b.setTexture(&bttex);
			if (b.isIntersected(mpos))
				b.setColor(mix(bcolor, sf::Color::White));
			else b.setColor(bcolor);
			if (b.isPressed(sf::Mouse::Button::Left, mpos))
				return k;
			b.setPosition(Vector2f(bpos.x, bpos.y + (k - 1) * (res.y/24.f + bsize.y)));
			b.setFontColor(sf::Color(0, 0, 0));
			window.draw(b);
			k++;
		}
		window.draw(txt);
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
	std::vector<Vector2u> resols = { {800, 600}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}, {2560, 1440} }; // = resolutions
	if (!std::any_of(resols.begin(), resols.end(), [ures](Vector2u v) {return v == ures;}))
	{
		unsigned int n = window.getSize().x;
		if (n < resols[0].x)
			resols.insert(resols.begin(), window.getSize());
		else if (n > resols[resols.size() - 1].x)
			resols.insert(resols.end(), window.getSize());
		else
		{
			int i = 0;
			auto a = next(resols.begin());
			while (!(resols.at(i).x <= n and n <= resols.at(++i).x)) a++;
			resols.insert(a, window.getSize());
		}
	}
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


	int mode_id = engine::reverse_modes[engine::getInfoVideoMode()]; // video mode index
	std::string strmode = "Windowed";
	switch (mode_id)
	{
	case 1:
		strmode = "Borderless";
		break;
	case 2:
		strmode = "Fullscreen";
	}
	Button switcherWMode = Button(bsize2, strmode, font, ures.y / 27u); // window mode switcher

	Button switcherVsync = Button(swsize, "+", font, ures.y / 27u); // vsync mode switcher
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

	sf::Text tres("Resolution", font);
    sf::Text tfps("Framerate limit", font);
    sf::Text twmode("Window mode", font);
    sf::Text tvsync("Vsync", font);
    std::vector<sf::Text> txts;
    txts.push_back(tres);
    txts.push_back(tfps);
    txts.push_back(twmode);
    txts.push_back(tvsync);
    Vector2u bres = window.getSize();

	float w;
	uint8_t i, j, n, k, t;
	int p1 = static_cast<int>(engine::math::get_index(resols, window.getSize()));
	int p2 = 2; // p2 - framerate id
	Vector2u r = window.getSize();
	unsigned int fr = engine::getInfoFramerateLimit();
	bool vsy = engine::getInfoVsync();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized: // if screen was resized
				{
					sf::FloatRect varea = sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height);
					window.setView(sf::View(varea));
				}
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
				buttons[9].setSize(bsize2); // wmode
				buttons[10].setSize(swsize); // switcher vsync
				for (auto &b : buttons)
					b.setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
			}
		}
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		//code
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;

		k = 1, j = i = t = 0, w = 0.f;
		for (auto &b : buttons)
		{
			if (b.isIntersected(mpos) && k != ResolutionViewer && k != FramerateViewer)
				b.setColor(mix(bcolor, sf::Color::White));
			else b.setColor(bcolor);

			//button positioning
			if (k == Back)
                b.setPosition(Vector2f(0, 0));

			else if (k == Save or k == Reset)
				b.setPosition(Vector2f((++i) * res.x/5.0f, res.y - res.y/10) - b.getSize());
			else
			{
				n = static_cast<uint8_t>(abs(floor(j / 3.f)));
				w = j % 3 == 0 ? 0 : w + buttons[k-2].getSize().x;
				b.setPosition(Vector2f(bpos.x + w + (j % 3)*res.x/27.f + res.x/5.0f, bpos.y + n*bsize.y*1.5f));
				if (k == VideoModeSwitcher or k == VsyncSwitcher) j+=2;
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
					r = resols[p1];
					fr = framerates[p2];
					engine::resetInfoResolution(r.x, r.y);
					engine::resetInfoVsync(vsync);
					engine::resetInfoFramerateLimit(fr);
					engine::resetInfoVideoMode(mode_id);
					window.close();
					window.create(sf::VideoMode(r.x, r.y, sf::VideoMode::getDesktopMode().bitsPerPixel), "Card Wars", engine::video_modes[mode_id]);
					window.setVerticalSyncEnabled(vsync);
					window.setFramerateLimit(fr);
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
					buttons[9].setSize(bsize2); // wmode
					buttons[10].setSize(swsize); // switcher vsync
					for (auto &b : buttons)
						b.setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
					break;
				case Reset:
					engine::create_infof();

					break;
				case LeftResolutionSwitcher:
					p1 = std::max(p1 - 1, 0);
					buttons[4].setString(std::to_string(resols[p1].x) + " x " + std::to_string(resols[p1].y));
					break;
				case ResolutionViewer:
					buttons[4].setString(":P");
					break;
				case RightResolutionSwitcher:
					p1 = (int) std::min(size_t(p1 + 1), resols.size() - 1);
					buttons[4].setString(std::to_string(resols[p1].x) + " x " + std::to_string(resols[p1].y));
					break;
				case LeftFramerateSwicher:
					p2 = std::max(p2 - 1, 0);
					buttons[7].setString(std::to_string(framerates[p2]));
					break;
				case FramerateViewer:
					buttons[7].setString(":D");
					break;
				case RightFramerateSwitcher:
					p2 = (int) std::min(size_t(p2 + 1), framerates.size() - 1);
					buttons[7].setString(std::to_string(framerates[p2]));
					break;
				case VideoModeSwitcher:
					++mode_id %= engine::getVideoModesCount(); // c++ moment
					switch (mode_id)
					{
					case 0:
						b.setString("Windowed");
						break;
					case 1:
						b.setString("Borderless");
						break;
					case 2:
						b.setString("Fullscreen");
					}
					break;
				case VsyncSwitcher:
					vsync = !vsync;
					if (vsync) b.setString("V");
					else if (!vsync) b.setString("");
					break;
				}
            }
            k++;
            window.draw(b);
		}
		for (auto &txt : txts) {
            txt.setScale(res.x / bres.x, res.y / bres.y);
            txt.setPosition(Vector2f(res.x/5.0f, (++t) * res.y / 23.5f + res.y/10.5f));
            t++;
            window.draw(txt);
        }
		window.display();
	}
}

void start_game(sf::RenderWindow &window)
{
	using engine::Button;
	using engine::math::clamp;
	using engine::math::norm;
	using engine::math::pi;
	using engine::math::rad;
	using Vec2f = sf::Vector2f;
	using engine::math::mix;
	using Rect = sf::RectangleShape;
	using namespace engine::cards;
	using namespace parametrs;
	const Vec2f res = Vec2f(window.getSize());
	sf::Mouse m;
	Vec2f mpos = Vec2f(m.getPosition(window));
	engine::collections::SuperCollection supc(window.getSize());
	engine::Deck deck(&supc, 3, res/30.f, res.y);
	deck.setPosition(res.x/2.5f, 0);
	float sens = 50; // slider speed
	float senst = 0;
	while (window.isOpen())
	{
		float d1 = 0;
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseWheelMoved:
				d1 = clamp(static_cast<float>(event.mouseWheel.delta), -1, 1);
			}
		mpos = Vec2f(m.getPosition(window));
		window.clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;
		senst = d1 != 0?  senst + sens / 4 : 0;
		deck.setSliderPos(deck.getSliderPos().y - senst * d1);
		if (deck.sliderIsClicked(sf::Mouse::Button::Left, mpos) or deck.sliderIsHold(sf::Mouse::Button::Left))
			deck.setSliderPos(mpos.y - deck.getSliderSize().y / 2);
		window.draw(deck);
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
				break;
			}
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		//code
		if (back.isIntersected(mpos))
			back.setColor(mix(bcolor, sf::Color::White));
		else back.setColor(bcolor);
		if (back.isPressed(sf::Mouse::Button::Left, mpos) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;
		window.draw(rect);
		window.draw(text);
		window.draw(back);
		window.draw(cardlol);
		window.display();
	}
}
