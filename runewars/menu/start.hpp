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
		Vec2f edge_size = {15, 15};
		Button edge1(edge_size, "", font);
		edge1.setPosition(100, 300); // default
		Button edge2(edge_size, "", font);
		edge2.setPosition(800, 300); // default
		Button edge3(edge_size, "", font);
		edge3.setPosition(300, 500);
		bool resize = false;
		for (auto edge : { edge1, edge2, edge3 })
			edge.setOrigin(edge.getSize()/2.f);
		engine::Curve curve({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return;
			mpos = Vec2f(m.getPosition(window));
			if (edge1.isAttached(sf::Mouse::Left, mpos))
			{
				edge1.setPosition(mpos);
				resize = true;
			}
			else if (edge2.isAttached(sf::Mouse::Left, mpos))
			{
				edge2.setPosition(mpos);
				resize = true;
			}
			else if (edge3.isAttached(sf::Mouse::Left, mpos))
			{
				edge3.setPosition(mpos);
				resize = true;
			}
			else resize = false;
			window.clear();
			if (resize)
				curve = engine::Curve({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
			window.draw(edge1);
			window.draw(edge2);
			window.draw(edge3);
			window.draw(curve);
			
			window.display();
		}
	}
}
