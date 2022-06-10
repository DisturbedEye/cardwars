#pragma once

inline void menu::about_us(sf::RenderWindow &window)
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
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		float time = static_cast<float>(clock()) / CLOCKS_PER_SEC;
		sht.setUniform("t", time);
		mpos = Vector2f(m.getPosition(window));
		window.clear();
		//code
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;
		if (back.isIntersected(mpos))
			back.setColor(mix(bcolor, sf::Color::White));
		else back.setColor(bcolor);
		if (back.isPressed(sf::Mouse::Button::Left, mpos))
			return;
		sht.render();
		rect.setTexture(sht.getTexture());
		window.draw(rect);
		window.draw(text);
		window.draw(back);
		window.draw(cardlol);
		window.display();
	}
}
