#pragma once

namespace engine
{
	template<class Shape, engine::ScrollType ScType>
	class Slider : public Clickable, public Shape
	{
		float minV = 0.f; // min value
		float maxV = 0.f; // max value

		public:
		Slider(const Shape &sh, float _minV = 0, float _maxV = 0) : Shape(sh), minV(_minV), maxV(_maxV) {}
		Slider() = default;
		float getMin() const { return minV; }
		float getMax() const { return maxV; }
		void setLimit(const float &_min, const float &_max)
		{
			if (ScType == ScrollType::Vertical) 
			{
				minV = std::min(_min, _max);
				maxV = std::max(this->getGlobalBounds().top, std::max(_min, _max)); // max value not less than slider size
			} else
			{
				minV = std::min(_min, _max);
				maxV = std::max(this->getGlobalBounds().left, std::max(_min, _max)); // max value not less than slider size
			}
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
		Vec2f coef() const { return Vec2f(Shape::getPosition() / maxV); }
		bool isIntersected(const Vec2f &p) const override
		{
			Shape shape(*this);
			return math::contains(shape, p);
		}
	private:
		float clampY(const Vec2f &p) const
		{
			return math::clamp(p.y, this->minV, this->maxV - this->getGlobalBounds().height);
		}
		float clampX(const Vec2f &p) const
		{
			return math::clamp(p.x, this->minV, this->maxV - this->getGlobalBounds().width);
		}
	};
}