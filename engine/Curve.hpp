#pragma once

namespace engine
{
	class Curve : sf::VertexArray // now it doesn't work
	{
		float step;
	public:
		Curve(const std::vector<Vec2f> &points);
		void resize(const size_t &count);
	private:
		static Vec2f count_points(const std::vector<Vec2f> &points, const float &t);
	};
	inline Curve::Curve(const std::vector<Vec2f> &points) : VertexArray(sf::Lines, 25)
	{
		size_t i = 0;
		step = 1.f / static_cast<float>(getVertexCount());
		for(float t = 0.f; t < 1.0f; t = math::clamp(t + step, 0.f, 1.f))
			(*this)[i++].position = count_points(points, t);
	}
	inline void Curve::resize(const size_t& count)
	{
		VertexArray::resize(count);
		step = 1.f / static_cast<float>(count);
	}

	inline Vec2f Curve::count_points(const std::vector<Vec2f> &points, const float &t)
	{
		std::vector<Vec2f> next_points;
		if (points.empty())
			return {};
		if (points.size() == 1)
			return points[0];
		for (size_t i = 0, j = 1; j < points.size(); i++, j++)
		{
			auto &p1 = points[i];
			auto &p2 = points[j];
			const float &x1 = p1.x, x2 = p2.x;
			const float &y1 = p1.y, y2 = p2.y;
			float x3 = x1 + (x2 - x1) * t;
			float y3 = y1 + (y2 - y1) * t;
			next_points.emplace_back(x3, y3);
		}
		return count_points(points, t);
	}

}

