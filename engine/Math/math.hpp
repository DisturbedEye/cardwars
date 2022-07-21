#pragma once
namespace engine
{
	template<typename T>
	Vec2<T> operator+(const Vec2<T> &v, const T &c)
	{
		return Vec2<T>(v.x + c, v.y + c);
	}

	template<typename T>
	Vec2<T> operator-(const Vec2<T> &v, const T &c)
	{
		return Vec2<T>(v.x - c, v.y - c);
	}
	namespace math
	{
		inline float around(const float &x, const int n)
		{
			return std::roundf(x * powf(10, static_cast<float>(n))) / powf(10, static_cast<float>(n));
		}

		inline bool belongs(const float &x, const float &m, const float &n)
		{
			return x <= m and x >= n or x <= n and x >= m;
		}

		inline float time()
		{
			return static_cast<float>(clock()) / CLOCKS_PER_SEC;
		}

		inline bool contains(const Rect &rect, const Vec2f &p)
		{
			return rect.getGlobalBounds().contains(p);
		}

		inline bool contains(const sf::FloatRect &rect, const Vec2f &p)
		{
			return rect.contains(p);
		}

		inline bool contains(const Convex &polygon, const Vec2f &p)
		{ // only for convex
			bool ins = true;
			const Vec2f pp = polygon.getPosition();
			Vec2f p1 = pp + polygon.getPoint(0), p2;
			for (int i = static_cast<int>(polygon.getPointCount()) - 1; i >= 0; i--)
			{
				p2 = pp + polygon.getPoint(i);
				ins = ins && (p1.y - p2.y) * p.x + (p2.x - p1.x) * p.y <= p1.y * p2.x - p1.x * p2.y;
				p1 = p2;
			}
			return ins;
		}
		inline bool contains(const Circle &circle, const Vec2f &point)
		{
			const float &x = point.x;
			const float &y = point.y;
			const float r = circle.getRadius();
			const float p = circle.getScale().x;
			const float q = circle.getScale().y;
			const Vec2f cor = circle.getOrigin();
			const float x0 = circle.getPosition().x + r * p - cor.x * p;
			const float y0 = circle.getPosition().y + r * q - cor.y * q;
			return powf((x - x0) / p, 2.f) + powf((y - y0) / q, 2.f) <= powf(r, 2.f);
		}
		inline float length(const Vec2f &v)
		{
			return hypotf(v.x, v.y);
		}

		inline float length(const float& x, const float& y)
		{
			return hypotf(x, y);
		}

		inline sf::Color mix(const sf::Color &c1, const sf::Color &c2)
		{
			return sf::Color((c1.r + c2.r) / 2, (c1.g + c2.g) / 2, (c1.b + c2.b) / 2, (c1.a + c2.a) / 2);
		}

		inline float clamp(const float &x, const float &minX, const float maxX)
		{
			return std::min(maxX, std::max(x, minX));
		}
	}
}
