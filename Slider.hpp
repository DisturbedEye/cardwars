#pragma once


class engine::Slider : public sf::Drawable, public Clickable
{
public:
	enum class Type
	{
		Vertical, Horizontal
	};
	Slider(const Rect &r, float, float, Type t);
	Slider(const Vec2f &s, float, float, Type t);
	Slider() : Clickable() {}
	void setPosition(const Vec2f &);
	void setPosition(const float &x, const float &y) { setPosition(Vec2f(x, y)); }
	void setSize(const Vec2f &);
	void setOrigin(const Vec2f &);
	void setOrigin(const float &x, const float &y) { setOrigin(Vec2f(x, y)); }
	void setLimit(const float &, const float &);
	void setFillColor(const sf::Color &clr) { rect.setFillColor(clr); }
	void setOutlineColor(const sf::Color &clr) { rect.setOutlineColor(clr); }
	void setOutlineThickness(const float &thickness) { rect.setOutlineThickness(thickness); }
	Vec2f getPosition() const;
	Vec2f getSize() const;
	Vec2f getOrigin() const;
	sf::Color getOutlineColor() const { return rect.getOutlineColor(); }
	sf::Color getFillColor() const { return rect.getFillColor(); }
	float getOutlineThickness() const { return rect.getOutlineThickness(); }
	float getMin() const;
	float getMax() const;
	Type getType() const;
	sf::FloatRect getLocalBounds() const { return rect.getLocalBounds(); }
	sf::FloatRect getGlobalBounds() const { return rect.getGlobalBounds(); }
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override;
private:
	float minV = 0;
	float maxV = 0;
	void clampPos();
	Type type = Type::Vertical;
};


inline engine::Slider::Slider(const Rect &r, const float _minV, const float _maxV, const Type t)
	: Clickable(r), minV(_minV), maxV(_maxV), type(t) {}

inline engine::Slider::Slider(const Vec2f &s, const float _minV, const float _maxV, const Type t)
	: Clickable(s), minV(_minV), maxV(_maxV), type(t) {}

inline void engine::Slider::setPosition(const Vec2f &pos)
{
	if (type == Type::Vertical)
		rect.setPosition(pos.x, math::clamp(pos.y, minV, maxV));
	else rect.setPosition(math::clamp(pos.x, minV, maxV), pos.y);
}

inline void engine::Slider::setSize(const Vec2f &s)
{
	rect.setSize(s);
}

inline void engine::Slider::setOrigin(const Vec2f &_or)
{
	rect.setOrigin(_or);
}

inline void engine::Slider::setLimit(const float &_min, const float &_max)
{
	minV = _min;
	maxV = _max;
}

inline engine::Vec2f engine::Slider::getPosition() const
{
	return rect.getPosition();
}

inline engine::Vec2f engine::Slider::getSize() const
{
	return rect.getSize();
}

inline engine::Vec2f engine::Slider::getOrigin() const
{
	return rect.getOrigin();
}

inline float engine::Slider::getMin() const
{
	return minV;
}

inline float engine::Slider::getMax() const
{
	return maxV;
}

inline engine::Slider::Type engine::Slider::getType() const
{
	return type;
}

inline void engine::Slider::draw(sf::RenderTarget &win, sf::RenderStates st) const
{
	win.draw(rect);
}

inline void engine::Slider::clampPos()
{
	if (type == Type::Horizontal)
		rect.setPosition(math::clamp(rect.getPosition().x, minV, maxV), rect.getPosition().y);
	else 
		rect.setPosition(rect.getPosition().x, math::clamp(rect.getPosition().y, minV, maxV));
}
