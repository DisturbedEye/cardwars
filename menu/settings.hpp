#pragma once
inline void menu::settings(sf::RenderWindow &window)
{
	/*
	* settings
	* screen resolution
	* frame limit
	* audio (later add)
	* other settings
	*/
	using engine::Vec2f, engine::Vec2u;
	using std::min, std::max;
	using engine::math::mix;
	using engine::Circle, engine::ScrollType, engine::Rect,
		engine::Button;
	using namespace parametrs;
	sf::Mouse m;
	Vec2f mpos;
	Vec2u ures = window.getSize();
	Vec2f res = Vec2f(ures);
	std::vector<Vec2u> resols = { {800, 600}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}, {2560, 1440} }; // = resolutions
	if (!std::any_of(resols.begin(), resols.end(), [ures](Vec2u v) {return v == ures; }))
	{ // sorting a resolutions
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
	Vec2f bpos = Vec2f(res.x / 3.f, res.y / 8.f); // button position
	Vec2f bsize = Vec2f(res.x / 9.6f, res.y / 18.f); // button size
	Vec2f bsize2 = Vec2f(res.x / 4.8f, res.y / 18.f); // screen buttons size
	Vec2f swsize = Vec2f(res.x / 32.f, res.y / 18.f); // switcher size
	sf::Color bcolor = sf::Color(115, 1, 4); // button color (reddish for me plz)
	auto &font = loadFont();
	// buttons
	Button backB = Button(bsize, "Back", font, ures.y / 27u); // save
	Button resetB = Button(bsize, "Reset", font, ures.y / 27u); // reset
	Button saveB = Button(Vec2f(bsize), "Save", font, ures.y / 27u);
	Button switcherL = Button(swsize, "<", font, ures.y / 27u); // left resolution switcher
	Button switcherR = Button(swsize, ">", font, ures.y / 27u); // right resolution switcher
	std::string ressx = std::to_string(window.getSize().x); // string resolution x
	std::string ressy = std::to_string(window.getSize().y); // string resolution y
	Button rScreen = Button(bsize2, ressx + " x " + ressy, font, ures.y / 27u); // resolution display through button


	int mode_id = engine::reverse_modes[engine::getInfoVideoMode()]; // video mode index
	auto get_mode_name([&mode_id]()
	{
		std::string strmode = "Windowed";
		switch (mode_id)
		{
		case 1:
			strmode = "Borderless";
			break;
		case 2:
			strmode = "Fullscreen";
		}
		return strmode;
	});

	Button switcherWMode = Button(bsize2, get_mode_name(), font, ures.y / 27u); // window mode switcher

	Button switcherVsync = Button(swsize, "V", font, ures.y / 27u); // vsync mode switcher
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

	std::vector<Button *> buttons;
	buttons.push_back(&backB);	      // 1
	buttons.push_back(&saveB);         // 2
	buttons.push_back(&resetB);        // 3
	buttons.push_back(&switcherL);     // 4
	buttons.push_back(&rScreen);       // 5
	buttons.push_back(&switcherR);     // 6
	buttons.push_back(&switcherLF);    // 7
	buttons.push_back(&fScreen);       // 8
	buttons.push_back(&switcherRF);    // 9
	buttons.push_back(&switcherWMode); // 10
	buttons.push_back(&switcherVsync); // 11

	sf::Text tres("Resolution", font);
	sf::Text tfps("Framerate limit", font);
	sf::Text twmode("Window mode", font);
	sf::Text tvsync("Vsync", font);
	std::vector<sf::Text *> txts;
	txts.push_back(&tres);
	txts.push_back(&tfps);
	txts.push_back(&twmode);
	txts.push_back(&tvsync);
	Vec2u bres = window.getSize();

	sf::SoundBuffer sb1;
	sf::SoundBuffer sb2;
	sb1.loadFromFile("audio\\sound1.ogg");
	sb2.loadFromFile("audio\\sound2.ogg");
	sf::Sound s1;
	sf::Sound s2;
	s1.setBuffer(sb1);
	s2.setBuffer(sb2);

	float w;
	int p1 = static_cast<int>(engine::math::get_index(resols, window.getSize()));
	int p2 = 2; // p2 - framerate id
	Vec2u r = window.getSize();
	unsigned int fr = engine::getInfoFramerateLimit();
	auto win_resize([&buttons, &bsize, &swsize, &bsize2, &res, &bpos](const Vec2u &size)
	{ // resizes a window
		res = Vec2f(size);
		bpos = Vec2f(res.x / 3.f, res.y / 8.f); // button position
		bsize = Vec2f(res.x / 9.6f, res.y / 18.f); // button size
		bsize2 = Vec2f(res.x / 4.8f, res.y / 18.f); // screen buttons size
		swsize = Vec2f(res.x / 32.f, res.y / 18.f); // switcher size
		buttons[0]->setSize(bsize); // back
		buttons[1]->setSize(bsize); // save
		buttons[2]->setSize(bsize); // reset
		buttons[3]->setSize(swsize); // switcher l
		buttons[4]->setSize(bsize2); // rtarget
		buttons[5]->setSize(swsize); // switcher r
		buttons[6]->setSize(swsize); // fswitcher l
		buttons[7]->setSize(bsize2); // ftarget
		buttons[8]->setSize(swsize); // fswitcher r
		buttons[9]->setSize(bsize2); // wmode
		buttons[10]->setSize(swsize); // switcher vsync
		for (auto &b : buttons)
			b->setCharacterSize((uint32_t)abs(floor(engine::math::length(res))) / 54u);
	});
	auto reopen_window([&window, &r, &mode_id, &fr, &win_resize](const bool &vsync)
	{ // reopens window
		window.close();
		window.create(sf::VideoMode(r.x, r.y, sf::VideoMode::getDesktopMode().bitsPerPixel), "Card Wars", engine::video_modes[mode_id]);
		window.setVerticalSyncEnabled(vsync);
		window.setFramerateLimit(fr);
		win_resize(window.getSize());
	});
	Vec2f slider_pos = { 3.f * res.x / 5.f, 7.f * res.y / 12.f };
	engine::Slider<Circle, ScrollType::Horizontal> example(Circle(25.f), slider_pos.x, res.x - res.x / 12.f);
	example.setPosition(slider_pos);
	sf::Texture textr;
	textr.loadFromFile("images/floppa.png");

	example.setTexture(&textr);
	bool a = false;
	uint8_t i, j, n, k, t, tmp = 0, pp = 0;
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
			win_resize(window.getSize());
			}
		}
		mpos = Vec2f(m.getPosition(window));
		window.clear();
		//code
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;

		k = 1, j = i = t = 0, w = 0.f;
		for (auto &b : buttons)
		{
			if (b->isIntersected(mpos) && k != ResolutionViewer && k != FramerateViewer) {
				b->setColor(mix(bcolor, sf::Color::White));
				while (pp == 0) {
					s2.play();
					pp = 1;
				}
			}
			else {
				b->setColor(bcolor);
				tmp++;
			}

			//button positioning
			if (k == Back)
				b->setPosition(Vec2f(0, 0));

			else if (k == Save or k == Reset)
				b->setPosition(Vec2f((++i) * res.x / 5.0f, res.y - res.y / 10) - b->getSize());
			else
			{
				n = static_cast<uint8_t>(abs(floor(j / 3.f)));
				w = j % 3 == 0 ? 0 : w + buttons[k - 2]->getSize().x;
				b->setPosition(Vec2f(bpos.x + w + j % 3 * res.x / 27.f + res.x / 5.0f, bpos.y + n * bsize.y * 1.5f));
				if (k == VideoModeSwitcher or k == VsyncSwitcher) j += 2;
				j++;
			}
			if (b->isPressed(sf::Mouse::Button::Left, mpos))
			{
				s1.play();
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
					reopen_window(vsync);
					break;
				case Reset:
					engine::create_infof();
					r = engine::getInfoResolution();
					fr = engine::getInfoFramerateLimit();
					vsync = engine::getInfoVsync();
					mode_id = engine::reverse_modes[engine::getInfoVideoMode()];
					reopen_window(vsync);
					break;
				case LeftResolutionSwitcher:
					p1 = std::max(p1 - 1, 0);
					buttons[4]->setString(std::to_string(resols[p1].x) + " x " + std::to_string(resols[p1].y));
					break;
				case ResolutionViewer:
					buttons[4]->setString(":P");
					break;
				case RightResolutionSwitcher:
					p1 = (int)std::min(size_t(p1 + 1), resols.size() - 1);
					buttons[4]->setString(std::to_string(resols[p1].x) + " x " + std::to_string(resols[p1].y));
					break;
				case LeftFramerateSwicher:
					p2 = std::max(p2 - 1, 0);
					buttons[7]->setString(std::to_string(framerates[p2]));
					break;
				case FramerateViewer:
					buttons[7]->setString(":D");
					break;
				case RightFramerateSwitcher:
					p2 = (int)std::min(size_t(p2 + 1), framerates.size() - 1);
					buttons[7]->setString(std::to_string(framerates[p2]));
					break;
				case VideoModeSwitcher:
					++mode_id %= engine::getVideoModesCount();
					switch (mode_id)
					{
					case 0:
						b->setString("Windowed");
						break;
					case 1:
						b->setString("Borderless");
						break;
					case 2:
						b->setString("Fullscreen");
					}
					break;
				case VsyncSwitcher:
					vsync = !vsync;
					if (vsync) b->setString("V");
					else if (!vsync) b->setString("");
					break;
				}
			}
			k++;
			window.draw(*b);
		}
		for (auto &txt : txts)
		{
			txt->setScale(res.x / bres.x, res.y / bres.y);
			txt->setPosition(Vec2f(res.x / 5.0f, (++t) * res.y / 23.5f + res.y / 10.5f));
			t++;
			window.draw(*txt);
		}
		if (tmp == 11) pp = 0;
		else tmp = 0;
		if (example.isClicked(sf::Mouse::Button::Left, mpos))
			a = true;
		if (!example.isHold(sf::Mouse::Button::Left))
			a = false;
		if (a)
			example.setPosition(mpos.x - example.getRadius(), slider_pos.y);
		window.draw(example);

		window.display();
	}
}
