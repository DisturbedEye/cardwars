#pragma once
template <class Shape>
engine::Button<Shape>::Button(const Shape sh)
	: shape(sh)
{
}

template<class Shape>
inline void engine::Button<Shape>::waitForAction(const bool &before, const bool &after, const Vec2f &p)
{
	if (math::inside(p, shape))
	{
		this->intersected = true;
		this->is_clicked = !before and after ? true : false;
		this->is_pressed = before and !after? true : false;
		this->is_hold = after;
	}
	else this->intersected = false;
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
inline bool engine::Button<Shape>::isPressed() const
{
	return this->is_pressed;
}

template<class Shape>
inline bool engine::Button<Shape>::isClicked() const
{
	return this->is_clicked;
}

template<class Shape>
inline bool engine::Button<Shape>::isIntersected() const
{
	return this->intersected;
}

template<class Shape>
inline bool engine::Button<Shape>::isHold() const
{
	return this->is_hold;
}

template<class Shape>
inline void engine::Button<Shape>::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(shape);
	window.draw(content);
}
