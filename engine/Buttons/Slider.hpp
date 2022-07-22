#pragma once

namespace engine
{
	template<class Shape, ScrollType ScType>
	class Slider : public ClickableObject, public Shape
	{
		float maxV = 0.f; // max value
		Vec2f start;
	public:
		Slider(const Shape &sh, const Vec2f &start, float _maxV) : Shape(sh), start(start)
		{
			setPosition(start);
			setLimit(_maxV);
		}
		Slider() = default;
		float getMax() const { return maxV; }
		Vec2f getStart() const { return start; }
		void setStart(const Vec2f &p) const { start = p; }
		void setLimit(const float &_max)
		{
			if (ScType == ScrollType::Vertical) 
				maxV = std::max(this->getGlobalBounds().height, _max) - this->getGlobalBounds().height; // max value not less than slider size
			else
				maxV = std::max(this->getGlobalBounds().width, _max) - this->getGlobalBounds().height; // max value not less than slider size
		}
		void setPosition(const Vec2f &pos)
		{
			if (ScType == ScrollType::Vertical)
				Shape::setPosition(Vec2f(pos.x, clampY(pos)));
			else Shape::setPosition(Vec2f(clampX(pos), pos.y));
		}
		void setPosition(const float &x, const float &y)
		{
			setPosition(Vec2f(x, y));
		}
		float coef() const
		{
			if (ScType == ScrollType::Vertical)
				return abs((Shape::getPosition().y - start.y) / maxV);
			return abs((Shape::getPosition().x - start.x) / maxV);
		}
		bool isIntersected(const Vec2f &p) const override
		{
			Shape shape(*this);
			return math::contains(shape, p);
		}
	private:
		float clampY(const Vec2f &p) const
		{
			return math::clamp(p.y, start.y, start.y + this->maxV);
		}
		float clampX(const Vec2f &p) const
		{
			return math::clamp(p.x, start.x, start.x + this->maxV);
		}
	};
}