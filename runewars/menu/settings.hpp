#pragma once
namespace rune::menu
{
	inline void settings(sf::RenderWindow &window)
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
		using namespace engine::algorithm;
		sf::Mouse m;
		Vec2f mpos;
		Vec2u ures = window.getSize();
		Vec2f res = Vec2f(ures);
		std::vector<Vec2u> resols = { {800, 600}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}, {2560, 1440} }; // = resolutions

		if (!in(ures, resols))
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
		const auto &font = fonts::RZSerif; // set font
		Settings parameters; // json settings
		std::vector<int> video_modes = {
			sf::Style::Close,		// Windowed
			sf::Style::None,		// Borderless
			sf::Style::Fullscreen	// Fullscreen
		};
		std::map<int, int> reverse_modes = { {video_modes[0], 0}, {video_modes[1], 1}, {video_modes[2], 2} };

		int mode_id = reverse_modes[parameters.getWindowMode()]; // video mode index
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

		std::vector<uint16_t> framerates = { 30, 59, 60, 75, 100, 120, 144, 240, 360 };
		Vec2f bsize = Vec2f(res.x / 9.6f, res.y / 18.f);	// button size
		Vec2f lrg_bsize = Vec2f(res.x / 4.8f, bsize.y);		// screen buttons size (large button size)
		Vec2f sml_bsize = Vec2f(res.x / 32.f, bsize.y);		// switcher size (small button size)
		sf::Color bcolor = sf::Color(115, 1, 4);			// button color (reddish for me plz)
		// buttons
		Button backB = Button(bsize, "Back", font);						    // back button
		Button resetB = Button(bsize, "Reset", font);					    // reset button
		Button saveB = Button(bsize, "Save", font);						    // save button
		Button switcherL{sml_bsize, "<", font };						    // left resolution switcher
		Button switcherR{sml_bsize, ">", font};							    // right resolution switcher
		std::string ressx = std::to_string(window.getSize().x);			    // string resolution x
		std::string ressy = std::to_string(window.getSize().y);			    // string resolution y
		Button rScreen = Button(lrg_bsize, ressx + " x " + ressy, font);    // resolution display through button
		Button switcherWMode = Button(lrg_bsize, get_mode_name(), font);    // window mode switcher
		Button switcherVsync = Button(sml_bsize, "V", font);			    // vsync mode switcher
		std::string frp = std::to_string(parameters.getFramerateLimit()); // string frame limit
		Button switcherLF = Button(sml_bsize, "<", font);				    // left switcher for framerate
		Button switcherRF = Button(sml_bsize, ">", font);				    // right switcher for framerate
		Button fScreen = Button(lrg_bsize, frp, font);					    // framerate display through button

		enum Buttons
		{
			Back = 1, Save = 2, Reset = 3,
			LeftResolutionSwitcher = 4, ResolutionViewer = 5, RightResolutionSwitcher = 6,
			LeftFramerateSwicher = 7, FramerateViewer = 8, RightFramerateSwitcher = 9,
			VideoModeSwitcher = 10, VsyncSwitcher = 11
		};
		//  to settings
		Button tres(lrg_bsize, "Resolution", font); // 1
		Button tfps(lrg_bsize, "Framerate limit", font); // 2
		Button twmode(lrg_bsize, "Window mode", font);	// 3
		Button tvsync(lrg_bsize, "Vsync", font);	// 4
		Button tmusicv(lrg_bsize, "Music", font);	// 5

		// volume slider
		struct VolumeSlider : engine::Slider<Circle, ScrollType::Horizontal>
		{
			VolumeSlider(const Slider<Circle, ScrollType::Horizontal> &slider, float volume) : Slider<Circle, ScrollType::Horizontal>(slider)
			{
				float rv = getRadius(); // radius of volume slider
				volume_line = Rect({ getMax() - rv / 2.f, rv });
				float rl = rv / 2.f;// volume line radius (half of height)
				Vec2f line_pos = { getStart().x + rv, getStart().y + rv / 2.f };
				c1 = c2 = Circle(rl);
				c1.setPosition(line_pos);
				c2.setPosition(c1.getPosition() + Vec2f(volume_line.getSize().x, 0));
				volume_line.setPosition(line_pos.x + rl, line_pos.y);
				setPosition(getStart().x + getMax() * volume / 100.f, getStart().y);
			}
			Circle c1;
			Circle c2;
			Rect volume_line;
		private:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const override
			{
				target.draw(c1, states);
				target.draw(c2, states);
				target.draw(volume_line, states);
				target.draw(engine::Slider(*this), states);
			}
		};
		VolumeSlider volume_slider({ Circle(15.f), Vec2f(0, 0), res.x / 3.f}, parameters.getMusicVolume());
		sf::Text volume_percent(std::to_string(parameters.getMusicVolume()) + "%", font); // percent of volume (Text)
		volume_percent.setPosition(volume_slider.getStart().x + volume_slider.getMax() + res.x / 39.f, volume_slider.getStart().y);
		//
		// sorting buttons in vectors
		std::vector txts{ &tres, &tfps, &twmode, &tvsync, &tmusicv };
		for (auto &txt : txts)
			txt->setFillColor(sf::Color(27, 27, 27));
		std::vector left_switchers{&switcherL, &switcherLF};
		std::vector right_switchers{ &switcherR, &switcherRF };
		std::vector central_buttons{ &rScreen, &fScreen, &switcherWMode, &switcherVsync };
		std::vector menu_buttons{ &backB, &saveB, &resetB };

		std::vector sbuttons{ // settings buttons (and button names)
			&tres, &switcherL, &rScreen, &switcherR,
			&tfps, &switcherLF, &fScreen, &switcherRF,
			&twmode, &switcherWMode,
			&tvsync, &switcherVsync,
			&tmusicv
		};
		std::vector middle_size_buttons = {
			&backB, &resetB, &saveB
		};
		// sounds
		sf::SoundBuffer sb1;
		sf::SoundBuffer sb2;
		sb1.loadFromFile("audio\\sound1.wav");
		sb2.loadFromFile("audio\\sound2.wav");
		sf::Sound s1;
		sf::Sound s2;
		s1.setBuffer(sb1);
		s2.setBuffer(sb2);
		std::vector buttons{
			&backB, &saveB, &resetB,
			&switcherL, &rScreen, &switcherR,
			&switcherLF, &fScreen, &switcherRF,
			&switcherWMode, &switcherVsync
		};

		auto set_settings_buttons_position([&sbuttons, &left_switchers, &right_switchers, &central_buttons, &txts, &menu_buttons, &volume_slider, &parameters](const Vec2f &res)
		{
			Vec2f default_cell_size = { 5.f * res.x / 24.f, res.y / 10.f };
			ngn::Table tab(4, 5, default_cell_size); // table
			tab.setColumnWidth(2, central_buttons[0]->getSize().x + res.x/16.f); // central_buttons[0] is pointer on screen viewer
			tab.setColumnWidth(1, left_switchers[0]->getSize().x + res.x/16.f); // left_switchers[0] is pointer on left screen switcher
			tab.setColumnWidth(0, txts[0]->getSize().x + res.x / 32.f); // txt[0] is pointer on resolution text
			Vec2f tsize = tab.getSize();
			tab.setPosition({ abs(res.x - tsize.x)/2.f, abs(res.y - tsize.y)/4.f});
			uint8_t l1, l2, l3, l4; // lines
			l1 = l2 = l3 = l4 = 0;
			Vec2f mp = tab.getPosition();
			Vec2f vs_pos = Vec2f(mp + tab.getCellPosition(1, 4)); // volume slider point
			volume_slider = VolumeSlider({Circle(volume_slider.getRadius()), Vec2f(vs_pos.x, vs_pos.y + tab.getCellSize(1, 4).y/6.f), volume_slider.getMax()}, parameters.getMusicVolume());
			for (auto &button : sbuttons) // sorting by columns
				{
					if (in(button, txts))
						button->setPosition(mp + tab.getCellPosition(0, l1++));
					else if (in(button, left_switchers))
						button->setPosition(mp + tab.getCellPosition(1, l2++));
					else if (in(button, central_buttons))
						button->setPosition(mp + tab.getCellPosition(2, l3++));
					else if (in(button, right_switchers))
						button->setPosition(mp + tab.getCellPosition(3, l4++));
				}
				auto &mb = menu_buttons;
				mb.at(0)->setPosition(res.x/32.f, res.y/18.f);
				mb.at(1)->setPosition(res.x - mb.at(0)->getPosition().x - mb.at(1)->getSize().x, res.y - mb.at(0)->getPosition().y - mb.at(1)->getSize().y);
				mb.at(2)->setPosition(mb.at(1)->getPosition().x - mb.at(2)->getSize().x - mb.at(0)->getPosition().x, res.y - mb.at(0)->getPosition().y - mb.at(2)->getSize().y);
			});
		auto win_resize([&set_settings_buttons_position, &menu_buttons, &bsize, &sml_bsize, &lrg_bsize, &res, &left_switchers, &right_switchers, &central_buttons](const Vec2u &size)
		{ // resizes a window
			res = Vec2f(size);
			bsize = Vec2f(res.x / 9.6f, res.y / 18.f);		// button size
			lrg_bsize = Vec2f(res.x / 4.8f, res.y / 18.f);	// screen buttons size
			sml_bsize = Vec2f(res.x / 32.f, res.y / 18.f);	// switcher size
			for (auto &b : menu_buttons)
				b->setSize(bsize);
			for (auto &b : left_switchers + right_switchers)
				b->setSize(sml_bsize);
			for (auto &b : central_buttons)
				b->setSize(lrg_bsize);
			set_settings_buttons_position(res);
		});
		auto reopen_window([&window, &win_resize, &parameters]
		{ // reopens window
			window.close();
			window.create(sf::VideoMode(parameters.getResolution().x, parameters.getResolution().y, sf::VideoMode::getDesktopMode().bitsPerPixel), "Rune Wars", parameters.getWindowMode());
			window.setVerticalSyncEnabled(parameters.getVsync());
			window.setFramerateLimit(parameters.getFramerateLimit());
			win_resize(window.getSize());
		});

		set_settings_buttons_position(res);

		volume_slider.setPosition(volume_slider.getStart().x + volume_slider.coef()*volume_slider.getMax(), volume_slider.getPosition().y);
		bool a = false;
		uint8_t k;
		auto p1 = std::find(resols.begin(), resols.end(), ures); // resolution iterator
		auto p2 = std::find(framerates.begin(), framerates.end(), parameters.getFramerateLimit()); // p2 - framerate iterator
		std::vector is_played = std::vector(9, false);
		bool vsync = parameters.getVsync();
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

			k = 1;
			for (auto &txt : txts)
				window.draw(*txt);
			for (auto &b : buttons)
			{
				if (b->isIntersected(mpos) && k != ResolutionViewer && k != FramerateViewer)
				{
					b->setFillColor(mix(bcolor, sf::Color::White));
					if (!is_played[k - 1])
						s2.play();
					is_played[k - 1] = true;
				}
				if(!b->isIntersected(mpos))
				{
					b->setFillColor(bcolor);
					s2.pause();
					is_played[k - 1] = false;
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
						ures = *p1;
						parameters.setResolution(ures);
						parameters.setFramerateLimit(*p2);
						parameters.setVsync(vsync);
						parameters.setWindowMode(video_modes[mode_id]);
						parameters.setMusicVolume(music_channel.getVolume());
						reopen_window();
						break;
					case Reset:
						parameters.resetToDefault();
						ures = parameters.getResolution();
						p2 = std::find(framerates.begin(), framerates.end(), parameters.getFramerateLimit());
						p1 = std::find(resols.begin(), resols.end(), ures);
						vsync = parameters.getVsync();
						mode_id = reverse_modes[parameters.getWindowMode()];
						reopen_window();
						break;
					case LeftResolutionSwitcher:
						if (p1 != resols.begin())
							p1--;
						rScreen.content.setString(std::to_string(p1->x) + " x " + std::to_string(p1->y));
						break;
					case ResolutionViewer:
						rScreen.content.setString(":P");
						break;
					case RightResolutionSwitcher:
						if (p1 != --resols.end()) p1++;
						rScreen.content.setString(std::to_string(p1->x) + " x " + std::to_string(p1->y));
						break;
					case LeftFramerateSwicher:
						if (p2 != framerates.begin()) p2--;
						fScreen.content.setString(std::to_string(*p2));
						break;
					case FramerateViewer:
						fScreen.content.setString(":D");
						break;
					case RightFramerateSwitcher:
						if (p2 != --framerates.end()) p2++;
						fScreen.content.setString(std::to_string(*p2));
						break;
					case VideoModeSwitcher:
						++mode_id %= static_cast<int>(video_modes.size());
						switch (mode_id)
						{
						case 0:
							b->content.setString("Windowed");
							break;
						case 1:
							b->content.setString("Borderless");
							break;
						case 2:
							b->content.setString("Fullscreen");
						}
						break;
					case VsyncSwitcher:
						vsync = !vsync;
						if (vsync) b->content.setString("V");
						else if (!vsync) b->content.setString("");
						break;
					}
				}
				k++;
				window.draw(*b);
			}
			// volume slider moving
			if (volume_slider.isAttached(sf::Mouse::Left, mpos)) 
			{
				volume_slider.setPosition(mpos.x - volume_slider.getRadius(), volume_slider.getPosition().y);
				float slvolume = volume_slider.coef() * 100; // slider position across volume
				music_channel.setVolume(slvolume);
			}
			window.draw(volume_slider);
			window.display();
		}
	}
}
