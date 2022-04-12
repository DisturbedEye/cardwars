#pragma once

template<class T>
size_t engine::math::get_index(const std::vector<T> &v, const T n)
{
	for (int i = 0; i < v.size(); i++)
		if (v[i] == n)
			return i;
	return -1;
}

template <class T>
inline bool engine::math::inside(const std::vector<T> &v, const T n)
{ // returns true if n inside v vector 
	for (auto i : v)
		if (i == n)
			return true;
	return false;
}

inline bool engine::math::around(const float &x, const int n) // округление до n чисел после зап€той
{
	return std::roundf(x * powf(10, static_cast<float>(n))) / powf(10, static_cast<float>(n));
}

inline bool engine::math::belongs(const float &x, const float &m, const float &n)
{
	return x <= m and x >= n or x <= n and x >= m;
}

inline bool engine::math::inside(const Vec2f &p, const Rect &rect)
{
	const Vec2f rs = rect.getSize();
	const Vec2f ro = rect.getPosition() - rect.getOrigin();
	return p.x >= ro.x and p.x <= ro.x + rs.x and p.y >= ro.y and p.y <= ro.y + rs.y;
}

inline bool engine::math::inside(const Vec2f &p, const Vec2f ro, const Vec2f rs)
{ // предпологаетс€ что ro - верхн€€ лева€ точка пр€моугольника
	return p.x >= ro.x and p.x <= ro.x + rs.x and p.y >= ro.y and p.y <= ro.y + rs.y;
}

inline float engine::math::length(const Vec2f &v)
{
	return hypotf(v.x, v.y);
}

bool engine::math::inside(const Vec2f &p, const Convex &polygon)
{ // только дл€ выпуклых многоугольников
	bool ins = true;
	const Vec2f pp = polygon.getPosition();
	Vec2f p1 = pp + polygon.getPoint(0), p2;
	for (int i = int(polygon.getPointCount()) - 1; i >= 0; i--)
	{
		p2 = pp + polygon.getPoint(i);
		ins = ins && (p1.y - p2.y) * p.x + (p2.x - p1.x) * p.y <= p1.y * p2.x - p1.x * p2.y;
		p1 = p2;
	}
	return ins;
}
inline bool engine::math::inside(const Vec2f &point, const Circle &circle)
{
	const float &x = point.x;
	const float &y = point.y;
	const float r = circle.getRadius();
	const float p = circle.getScale().x;
	const float q = circle.getScale().y;
	const Vec2f cor = circle.getOrigin();
	const float x0 = circle.getPosition().x + r*p - cor.x;
	const float y0 = circle.getPosition().y + r*q - cor.y;
	return powf((x - x0)/p, 2.f) + powf((y - y0)/q, 2.f) <= powf(r, 2.f);
}
sf::Color engine::math::mix(const sf::Color &c1, const sf::Color &c2)
{
	return sf::Color((c1.r + c2.r) / 2, (c1.g + c2.g) / 2, (c1.b + c2.b) / 2, (c1.a + c2.a) / 2);
}