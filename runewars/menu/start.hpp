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

		for (auto &edge : { &edge1, &edge2, &edge3 })
			edge->setOrigin(edge->getSize() / 2.f);

		engine::Curve curve({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
		curve.resize(100);
		sf::VertexArray facets(sf::LineStrip, curve.getEdges().size());
		
		Circle c(100);
		size_t i = 0;
		int inc = 1;
		float distance = 400;
		float speed = distance/100 * 20;
		while (window.isOpen())
		{
			mpos = Vec2f(m.getPosition(window));
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					edge1.push(event.type, mpos);
					edge2.push(event.type, mpos);
					edge3.push(event.type, mpos);
				}
				if (event.key.code == sf::Keyboard::Escape)
					if (engine::Clickable::isKeydown(event.type))
						return;
			}
			auto curve_edges = curve.getEdges();
			for (size_t k = 0; k < facets.getVertexCount(); k++)
				facets[k].position = Vec2f(curve_edges[k].x*edge1.getOrigin().x, curve_edges[k].y*edge1.getOrigin().y);
			if (edge1.isPushed())
			{
				edge1.setPosition(clamp(mpos, curve_block));
				curve.setEdges({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
			}
			if (edge2.isPushed())
			{
				edge2.setPosition(clamp(mpos, curve_block));
				curve.setEdges({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
			}
			if (edge3.isPushed())
			{
				edge3.setPosition(clamp(mpos, curve_block));
				curve.setEdges({ edge1.getPosition(), edge2.getPosition(), edge3.getPosition() });
			}
			if (i == curve.getVertexCount()) inc = -1;
			if (i == 0) inc = 1;
			Vec2f &point = curve[i+=inc].position;
			c.setPosition( distance - speed*(point.y - curve_block.top)/curve_block.height, 50);
			window.clear();
			window.draw(edge1);
			window.draw(edge2);
			window.draw(edge3);
			window.draw(c);
			window.draw(facets);
			window.draw(curve);
			
			window.display();
		}
	}
}
