#pragma once

namespace rune::menu
{
	inline void start(sf::RenderWindow &window)
	{
		using engine::Button;
		using emath::clamp;
		using engine::Vec2f;
		using engine::Vec2u;
		using emath::rad;
		using emath::mix;
		using engine::Rect;
		using emath::pi;
		const Vec2u ures = Settings::getResolution(Settings());
		const Vec2f res = Vec2f(ures);
		sf::Mouse m;
		Vec2f mpos = Vec2f(m.getPosition(window));
		auto &font = fonts::RZSerif;
		Vec2f edge_size = {15, 15};
		sf::FloatRect curve_block = { res, Vec2f(400, 400) };
		curve_block.left -= curve_block.width + edge_size.x;
		curve_block.top -= curve_block.height + edge_size.y;
		Button edge1(edge_size, "", font);
		edge1.setPosition(res.x - edge_size.x - curve_block.width, res.y - edge_size.y); // default
		Button edge2(edge_size, "", font);
		edge2.setPosition(res.x - edge_size.x - curve_block.width / 2.f, res.y - edge_size.y - curve_block.height / 2.f); // default
		Button edge3(edge_size, "", font);
		edge3.setPosition(res.x - edge_size.x, res.y - edge_size.y - curve_block.width);
		for (auto edge : { edge1, edge2, edge3 })
			edge.setOrigin(edge.getSize() / 2.f);

		engine::Curve curve({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
		
		sf::VertexArray facets(sf::LineStrip, curve.getVertexCount());
		Circle c(100);
		size_t i = 0;
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
				edge1.setPosition(clamp(mpos, curve_block));
				curve = engine::Curve({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
			}
			else if (edge2.isAttached(sf::Mouse::Left, mpos))
			{
				edge2.setPosition(clamp(mpos, curve_block));
				curve = engine::Curve({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
			}
			else if (edge3.isAttached(sf::Mouse::Left, mpos))
			{
				edge3.setPosition(clamp(mpos, curve_block));
				curve = engine::Curve({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
			}
			curve.resize(100);
			if (i == curve.getVertexCount()) i = 0;
			Vec2f &point = curve[i++].position;
			c.setPosition( 400 * (point.y - curve_block.top)/curve_block.height, 50);
			
			window.clear();
			window.draw(edge1);
			window.draw(edge2);
			window.draw(edge3);
			window.draw(c);
			window.draw(curve);
			
			window.display();
		}
	}
}
