#pragma once

namespace rune::menu
{
	inline void about_us(sf::RenderWindow &window)
	{
		using engine::Button;
		using sf::Vector2f;
		using engine::math::mix;
		typedef sf::RectangleShape Rect;
		const auto &font = fonts::RZSerif; // set font
		sf::Vector2u ures = window.getSize();
		Vector2f res = Vector2f(ures);
		Vector2f bsize = Vector2f(res.x / 9.6f, res.y / 18.f);
		Button back(bsize, "Back", font);
		Vector2f bpos = Vector2f(0, 0);
		sf::Mouse m;
		Rect rect = Rect(Vector2f(res.x * 2.f / 3.f, res.y));
		rect.setOrigin(rect.getSize() / 2.f);
		rect.setPosition(res.x / 2.f, res.y / 2.f);
		sf::Texture texture;
		texture.loadFromFile("images\\evolution.jpg");
		sf::Sprite cardlol;
		cardlol.setScale(0.5f, 0.5f);
		cardlol.setTexture(texture);
		cardlol.setPosition(rect.getPosition().x, res.y / 3.f);
		cardlol.setOrigin(cardlol.getGlobalBounds().width, 0);
		sf::Color bcolor = sf::Color(115, 101, 174); // button color
		sf::Text text("About Us:", font, ures.y / 27u);
		text.setPosition(res.x / 2.f - text.getGlobalBounds().width / 2.f, 0.f);
		back.setPosition(bpos); // setting back button pos
		Vector2f mpos;
		engine::ShaderTexture sht(ures, "backg.frag", sf::Shader::Fragment);
		sht.setUniform("u_res", res);
		
		while (window.isOpen())
		{
			mpos = Vector2f(m.getPosition(window));
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.key.code == sf::Keyboard::Escape)
					if (engine::Clickable::isKeydown(event.type))
						return;
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (back.isKeyup(event.type, mpos))
						return;
				}
			}
			float time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
			sht.setUniform("t", time);
			window.clear();
			//code
			if (back.isIntersected(mpos))
				back.setFillColor(mix(bcolor, sf::Color::White));
			else back.setFillColor(bcolor);
			sht.render();
			rect.setTexture(sht.getTexture());
			window.draw(rect);
			window.draw(text);
			window.draw(back);
			window.draw(cardlol);
			window.display();
		}
	}
}
