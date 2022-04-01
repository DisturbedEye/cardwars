#pragma once
template <class Shape>
class engine::Button : public sf::Drawable
{
public:
	Shape shape;
	sf::Text content;

	explicit Button(const Shape shape);
	Button(const Button<Shape> &b) : content(b.content), shape(b.shape) {}
	void setPosition(const Vec2f position);
	void setOrigin(const Vec2f origin);
	void setScale(const Vec2f scale);
	bool isPressed(const bool &before, const bool &after, const Vec2f &p) const;
	bool isClicked(const bool &before, const bool &after, const Vec2f &p) const;
	bool isIntersected(const Vec2f &p) const;
	bool isHold(const bool &after, const Vec2f &p) const;
private:
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
};

template <class Shape>
engine::Button<Shape>::Button(const Shape sh)
	: shape(sh)
{
	content.setOrigin(content.getGlobalBounds().width/2.f, 0.f);
}

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
inline bool engine::Button<Shape>::isPressed(const bool &before, const bool &after, const Vec2f &p) const
{
	return this->isIntersected(p) and before and !after;
}

template<class Shape>
inline bool engine::Button<Shape>::isClicked(const bool &before, const bool &after, const Vec2f &p) const
{
	return this->isIntersected(p) and !before and after;
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

template<class Shape>
inline void engine::Button<Shape>::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(shape);
	window.draw(content);
}
