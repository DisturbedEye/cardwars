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
		sf::VertexArray lines(sf::Lines, 2);
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
				}
			}
			mpos = Vec2f(m.getPosition(window));
			window.clear();
			window.draw(lines);
			window.display();
		}
	}
}
