#pragma once

namespace rune::menu
{
	inline void start(sf::RenderWindow &window)
	{
		using engine::Button;
		using emath::clamp;
		using engine::Vec2f;
		using engine::Vec2u;
		using emath::mix;
		using engine::Rect;
		using emath::pi;
		const Vec2u ures = window.getSize();
		const Vec2f res = Vec2f(ures);
		sf::Mouse m;
		Vec2f mpos = Vec2f(m.getPosition(window));
		auto &font = fonts::RZSerif;
		rcolls::Super all_cards(ures);
		auto deck = Deck(&all_cards, 3u, res.y / 3.f);
		const float &whl_speed = 10;
		Button shuffle(Vec2f{ 300, 75 }, "shuffle", font);
		shuffle.setPosition(2.f * res.x / 3.f - shuffle.getSize().x, res.y / 2.f);
		sf::Color shf_color = sf::Color(120, 240, 100);
		shuffle.setFillColor(shf_color);
		while (window.isOpen())
		{
			float d1 = 0;
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseWheelMoved:
					d1 = clamp(static_cast<float>(event.mouseWheel.delta), -1, 1);
				}
			}
			mpos = Vec2f(m.getPosition(window));
			window.clear();
			deck.setSliderPos(deck.getSlider().getPosition().y - d1 * whl_speed);
			if (shuffle.isIntersected(mpos))
				shuffle.setFillColor(mix(shf_color, sf::Color::White));
			else
				shuffle.setFillColor(shf_color);
			if (shuffle.isPressed(sf::Mouse::Button::Left, mpos))
				deck.shuffle();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				return;
			window.draw(shuffle);
			window.draw(engine::clip(deck));
			window.display();
		}
	}
}
