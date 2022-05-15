#pragma once


class engine::Slider : public sf::Drawable, public Clickable
{
public:
	Slider(const Rect &r, ScrollType t = ScrollType::Vertical, float = 0, float = 0);
	Slider(const Vec2f &s, ScrollType t = ScrollType::Vertical, float = 0, float = 0);
	Slider(const Slider &sl) : Clickable(sl.rect),
		minV(sl.minV), maxV(sl.maxV), type(sl.type) {}
	Slider(Slider &&sl) = default;
	Slider() : Clickable() {}
	~Slider() override = default;
	void setPosition(const Vec2f &);
	void setPosition(const float &x, const float &y) { setPosition(Vec2f(x, y)); }
	void setSize(const Vec2f &);
	void setOrigin(const Vec2f &);
	void setOrigin(const float &x, const float &y) { setOrigin(Vec2f(x, y)); }
	void setLimit(const float &, const float &);
	void setFillColor(const sf::Color &clr) { rect.setFillColor(clr); }
	void setTexture(const sf::Texture *texture) { rect.setTexture(texture); }
	Vec2f getPosition() const;
	Vec2f getSize() const;
	Vec2f getOrigin() const;
	sf::Color getFillColor() const { return rect.getFillColor(); }
	float getMin() const;
	float getMax() const;
	ScrollType getType() const;
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override;
	Slider &operator=(const Slider &sl) = default;
	Slider &operator=(Slider &&sl) = default;
private:
	float minV = 0;
	float maxV = 0;
	void clampPos();
	ScrollType type = ScrollType::Vertical;
};


inline engine::Slider::Slider(const Rect &r, ScrollType t, float _minV, float _maxV)
	: Clickable(r), minV(_minV), maxV(_maxV), type(t) {}

inline engine::Slider::Slider(const Vec2f &s, ScrollType t, float _minV, float _maxV)
	: Clickable(s), minV(_minV), maxV(_maxV), type(t) {}

inline void engine::Slider::setPosition(const Vec2f &pos)
{
	if (type == ScrollType::Vertical)
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

inline engine::ScrollType engine::Slider::getType() const
{
	return type;
}

inline void engine::Slider::draw(sf::RenderTarget &win, sf::RenderStates st) const
{
	win.draw(rect, st);
}

inline void engine::Slider::clampPos()
{
	if (type == ScrollType::Horizontal)
		rect.setPosition(math::clamp(rect.getPosition().x, minV, maxV), rect.getPosition().y);
	else 
		rect.setPosition(rect.getPosition().x, math::clamp(rect.getPosition().y, minV, maxV));
}
