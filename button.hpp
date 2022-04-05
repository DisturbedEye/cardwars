#pragma once
template <typename Shape>
struct engine::Button : public sf::Drawable
{
	explicit Button(const Shape &shape);
	Button(const Shape&, const sf::Text&);
	Button(const Shape&, const sf::String&, const sf::Font&, unsigned int = 30u);
	Button(const Button<Shape> &b) : content(b.content), shape(b.shape) {}
	Button() { shape = Shape(); content = sf::Text(); }
	void setPosition(const Vec2f position);
	void setOrigin(const Vec2f origin);
	void setScale(const Vec2f scale);

	Shape shape;
	sf::Text content;
	bool isPressed(sf::Keyboard::Key);
	bool isPressed(sf::Mouse::Button, const Vec2f &);
	bool isClicked(sf::Keyboard::Key);
	bool isClicked(sf::Mouse::Button, const Vec2f &p);
	bool isIntersected(const Vec2f &p) const;
	bool isHold(const bool &after, const Vec2f &p) const;
	void resetToCenter();
private:
	bool before = false;
	void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
};


template <class Shape>
engine::Button<Shape>::Button(const Shape &sh, const sf::String &string, const sf::Font &font, unsigned int char_size)
{
	shape = sh;
	content = sf::Text(string, font, char_size);
	content.setOrigin((content.getGlobalBounds().width - shape.getGlobalBounds().width)/2.f, 0.f);
}
template <class Shape>
engine::Button<Shape>::Button(const Shape &sh, const sf::Text &text)
{
	shape = sh;
	content = text;
	content.setOrigin((content.getGlobalBounds().width - shape.getGlobalBounds().width) / 2.f, 0.f);
}
template <class Shape>
engine::Button<Shape>::Button(const Shape &sh)
	: shape(sh)
{}

template<class Shape>
inline void engine::Button<Shape>::setPosition(const Vec2f position)
{
	shape.setPosition(position);
	content.setPosition(position);
}

template<class Shape>
inline void engine::Button<Shape>::setOrigin(const Vec2f origin)
{
	shape.setOrigin(origin);
	content.setOrigin(origin);
}

template<class Shape>
inline void engine::Button<Shape>::setScale(const Vec2f scale)
{
	shape.setScale(scale);
	content.setScale(scale);
}

template<class Shape>
inline bool engine::Button<Shape>::isPressed(sf::Keyboard::Key key) 
{
	const bool after = sf::Keyboard::isKeyPressed(key);
	const bool out = before and !after;
	before = after;
	return out;
}
template<class Shape>
inline bool engine::Button<Shape>::isPressed(sf::Mouse::Button button, const Vec2f &p) 
{
	const bool after = sf::Mouse::isButtonPressed(button);
	const bool out = this->isIntersected(p) and before and !after;
	before = after;
	return out;
}

template<class Shape>
inline bool engine::Button<Shape>::isClicked(sf::Keyboard::Key key)
{
	const bool after = sf::Keyboard::isKeyPressed(key);
	const bool out = !before and after;
	before = after;
	return out;
}
template<class Shape>
inline bool engine::Button<Shape>::isClicked(sf::Mouse::Button button, const Vec2f &p) 
{
	const bool after = sf::Mouse::isButtonPressed(button);
	const bool out = this->isIntersected(p) and !before and after;
	before = after;
	return out;
}

template<class Shape>
inline bool engine::Button<Shape>::isIntersected(const Vec2f &p) const
{
	return math::inside(p, shape);
}

template<class Shape>
inline bool engine::Button<Shape>::isHold(const bool &after, const Vec2f &p) const
{
	return this->isIntersected(p) and after;
}

template<typename Shape>
inline void engine::Button<Shape>::resetToCenter()
{
	content.setOrigin((content.getGlobalBounds().width - shape.getGlobalBounds().width) / 2.f, 0.f);
}

template<class Shape>
inline void engine::Button<Shape>::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(shape);
	if (content.getFont() != 0)
		window.draw(content);
}
