#pragma once

template<engine::ScrollType ScType>
class engine::Slider : public sf::Drawable, public Clickable
{
public:
	Slider(const Rect &r, float = 0, float = 0);
	Slider(const Vec2f &s, float = 0, float = 0);
	Slider(const Slider &sl) : Clickable(sl.rect),
		minV(sl.minV), maxV(sl.maxV) {}
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
};


template<engine::ScrollType ScType>
inline engine::Slider<ScType>::Slider(const Rect &r, float _minV, float _maxV)
	: Clickable(r), minV(_minV), maxV(_maxV) {}

template<engine::ScrollType ScType>
inline engine::Slider<ScType>::Slider(const Vec2f &s, float _minV, float _maxV)
	: Clickable(s), minV(_minV), maxV(_maxV) {}

template<>
inline void engine::Slider<engine::ScrollType::Vertical>::setPosition(const Vec2f &pos)
{
	rect.setPosition(pos.x, math::clamp(pos.y, minV, maxV - getSize().y));
}
template<>
inline void engine::Slider<engine::ScrollType::Horizontal>::setPosition(const Vec2f &pos)
{
	rect.setPosition(math::clamp(pos.x, minV, maxV - getSize().x), pos.y);
}
template<engine::ScrollType ScType>
inline void engine::Slider<ScType>::setSize(const Vec2f &s)
{
	rect.setSize(s);
}
template<engine::ScrollType ScType>
inline void engine::Slider<ScType>::setOrigin(const Vec2f &_or)
{
	rect.setOrigin(_or);
}
template<>
inline void engine::Slider<engine::ScrollType::Vertical>::setLimit(const float &_min, const float &_max)
{
	minV = std::min(_min, _max);
	maxV = std::max(getSize().y, std::max(_min, _max)); // max value not less than slider size
}
template<>
inline void engine::Slider<engine::ScrollType::Horizontal>::setLimit(const float &_min, const float &_max)
{
	minV = std::min(_min, _max);
	maxV = std::max(getSize().x, std::max(_min, _max)); // max value not less than slider size
}
template<engine::ScrollType ScType>
inline engine::Vec2f engine::Slider<ScType>::getPosition() const
{
	return rect.getPosition();
}
template<engine::ScrollType ScType>
inline engine::Vec2f engine::Slider<ScType>::getSize() const
{
	return rect.getSize();
}
template<engine::ScrollType ScType>
inline engine::Vec2f engine::Slider<ScType>::getOrigin() const
{
	return rect.getOrigin();
}
template<engine::ScrollType ScType>
inline float engine::Slider<ScType>::getMin() const
{
	return minV;
}
template<engine::ScrollType ScType>
inline float engine::Slider<ScType>::getMax() const
{
	return maxV;
}
template<engine::ScrollType ScType>
inline void engine::Slider<ScType>::draw(sf::RenderTarget &win, sf::RenderStates st) const
{
	win.draw(rect, st);
}