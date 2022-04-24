#pragma once

class engine::Clickable
{
	bool beforek = false; // for keyboard
	bool beforem = false; // for mouse
protected:
	Rect rect;
public:
	Clickable(const Rect &rect) : rect(rect) {}
	Clickable(const Vec2f &size) : rect(size) {}
	Clickable() {}
	// actions with buttons

	bool isPressed(sf::Mouse::Button);
	bool isClicked(sf::Mouse::Button);
	bool isPressed(sf::Keyboard::Key);
	bool isClicked(sf::Keyboard::Key);
	bool isHold(sf::Mouse::Button);
	bool isHold(sf::Keyboard::Key);
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	void setOutlineThickness(float thickness);
	void setOutlineColor(const sf::Color &clr);
	float getOutlineThickness() const;
	sf::Color getOutlineColor() const;
	// with shape
	bool isPressed(sf::Mouse::Button, const Vec2f &p);
	bool isClicked(sf::Mouse::Button, const Vec2f &p);
	bool isIntersected(const Vec2f &p) const;
	bool isHold(sf::Mouse::Button, const Vec2f &p);
};
inline sf::FloatRect engine::Clickable::getLocalBounds() const
{
	return rect.getLocalBounds();
}
inline sf::FloatRect engine::Clickable::getGlobalBounds() const
{
	return rect.getGlobalBounds();
}
inline void engine::Clickable::setOutlineThickness(float thickness)
{
	rect.setOutlineThickness(thickness);
}
inline void engine::Clickable::setOutlineColor(const sf::Color &clr)
{
	rect.setOutlineColor(clr);
}
inline float engine::Clickable::getOutlineThickness() const
{
	return rect.getOutlineThickness();
}
inline sf::Color engine::Clickable::getOutlineColor() const
{
	return rect.getOutlineColor();
}
inline bool engine::Clickable::isPressed(const sf::Mouse::Button button, const Vec2f &p)
{
	const bool after = sf::Mouse::isButtonPressed(button);
	const bool out = this->isIntersected(p) and beforem and !after;
	beforem = after;
	return out;
}

inline bool engine::Clickable::isClicked(sf::Mouse::Button button, const Vec2f &p)
{
	const bool after = sf::Mouse::isButtonPressed(button);
	const bool out = this->isIntersected(p) and !beforem and after;
	beforem = after;
	return out;
}


inline bool engine::Clickable::isIntersected(const Vec2f &p) const
{
	return math::inside(p, rect);
}

inline bool engine::Clickable::isHold(sf::Mouse::Button b, const Vec2f &p)
{
	const bool after = sf::Mouse::isButtonPressed(b);
	const bool out = this->isIntersected(p) and beforem and after;
	beforem = after;
	return out;
}
inline bool engine::Clickable::isPressed(sf::Mouse::Button b)
{
	const bool after = sf::Mouse::isButtonPressed(b);
	const bool out = beforem and after;
	beforem = after;
	return out;
}
inline bool engine::Clickable::isPressed(sf::Keyboard::Key k)
{
	const bool after = sf::Keyboard::isKeyPressed(k);
	const bool out = beforek and after;
	beforek = after;
	return out;
}
inline bool engine::Clickable::isClicked(sf::Mouse::Button b)
{
	const bool after = sf::Mouse::isButtonPressed(b);
	const bool out = beforem and after;
	beforem = after;
	return out;
}
inline bool engine::Clickable::isClicked(sf::Keyboard::Key k)
{
	const bool after = sf::Keyboard::isKeyPressed(k);
	const bool out = !beforek and after;
	beforek = after;
	return out;
}

inline bool engine::Clickable::isHold(sf::Mouse::Button b)
{
	const bool after = sf::Mouse::isButtonPressed(b);
	const bool out = beforem and after;
	beforem = after;
	return out;
}
inline bool engine::Clickable::isHold(sf::Keyboard::Key k)
{
	const bool after = sf::Keyboard::isKeyPressed(k);
	const bool out = beforek and after;
	beforek = after;
	return out;
}