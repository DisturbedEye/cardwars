#pragma once
namespace rune::menu
{
	inline Hierarchy main(sf::RenderWindow &window)
	{
		using engine::Vec2f, engine::Vec2u;
		using engine::math::mix;
		using engine::Circle, engine::ScrollType, engine::Rect,
			engine::Button;
		sf::Vector2u ures = window.getSize();
		sf::Vector2f res = sf::Vector2f(ures);
		sf::Mouse mouse;
		Vec2f bsize = Vec2f(res.x / 9.6f, res.y / 18.f); // button size
		Vec2f bpos = Vec2f(res.x / 12.f, res.y / 2.f); // button position
		const sf::Font &font = fonts::RZSerif; // font 
		sf::SoundBuffer sb1;
		sf::SoundBuffer sb2;
		sb1.loadFromFile("audio\\sound1.wav");
		sb2.loadFromFile("audio\\sound2.wav");
		sf::Sound s1;
		sf::Sound s2;
		s1.setBuffer(sb1);
		s2.setBuffer(sb2);
		sf::Texture bttex;
		sf::Texture bctex;
		if (bttex.loadFromFile("images\\button.png") && bctex.loadFromFile("images\\menu.png")) {
			bttex.setSmooth(true);
			bctex.setSmooth(true);
		}
		sf::RectangleShape r(Vec2f(res.x, res.y));
		r.setTexture(&bctex);
		// buttons
		Button start = Button(bsize, "Start", font);
		Button settings = Button(bsize, "Settings", font);
		Button about_us = Button(bsize, "About Us", font);
		Button exit = Button(bsize, "Exit", font);
		std::vector<Button*> buttons; // buttons too
		buttons.push_back(&start);	 // 1
		buttons.push_back(&settings); // 2
		buttons.push_back(&about_us); // 3
		buttons.push_back(&exit);	 // 4
		sf::Color bcolor = sf::Color(200, 200, 200); // button color
		Vec2f mpos;
		uint8_t k, n, tmp;
		sf::Text txt("Rune Wars", font);
		txt.setPosition(res.x / 6.f, res.y / 4.f);
		std::map<Button*, Hierarchy> actions = { {&start, Hierarchy::StartGame}, {&settings, Hierarchy::Settings}, {&about_us, Hierarchy::AboutUs},{&exit, Hierarchy::Exit} };
		txt.setScale(txt.getScale().x * 1.5f, txt.getScale().y * 1.5f);
		n = 0;
		tmp = 0;
		while (window.isOpen())
		{
			mpos = Vec2f(mouse.getPosition(window));
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (engine::Clickable::isKeydown(event.type))
						return Hierarchy::Exit;
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (auto &button : buttons)
					{
						if (button->isKeyup(event.type, mpos)) 
						{
							s1.play();
							return actions[button];
						}
					}
				}
			}
			window.clear(); // clears screen
			// code
			window.draw(r);
			window.draw(txt);
			k = 1;
			for (auto &b : buttons)
			{
				b->setTexture(&bttex);
				if (b->isIntersected(mpos)) {
					b->setFillColor(mix(bcolor, sf::Color::White));
					if (n == 0) 
					{
						n = 1;
						s2.play();
					}
				}
				else 
				{
					b->setFillColor(bcolor);
					tmp++;
				}
				b->setPosition(Vec2f(bpos.x, bpos.y + (k - 1) * (res.y / 24.f + bsize.y)));
				b->content.setFillColor(sf::Color(0, 0, 0));
				window.draw(*b);
				k++;
			}
			if (tmp == 4) n = 0;
			else tmp = 0;
			window.display();
		}
		
		return Hierarchy::Exit;
	}
}