#pragma once

// file with rest engine functions
template<class T>
std::vector<T> operator+(const std::vector<T> &u, const std::vector<T> &v)
{
	std::vector<T> a;
	for (auto &i : u) a.push_back(i);
	for (auto &i : v) a.push_back(i);
	return a;
}
template<class T>
std::vector<T> &operator+=(std::vector<T> &left, const std::vector<T> &right)
{
	left = left + right;
	return left;
}
template<class T>
ngn::Vec2<T> operator+(const ngn::Vec2<T> &left, const T &right)
{
	return ngn::Vec2<T>(left.x + right, left.y + right);
}

template<class T>
ngn::Vec2<T> &operator+=(ngn::Vec2<T> &left, const T &right)
{
	left = left + right;
	return left;
}

template<class T>
ngn::Vec2<T> operator-(const ngn::Vec2<T> &left, const T &right)
{
	return ngn::Vec2<T>(left.x - right, left.y - right);
}

template<class T>
ngn::Vec2<T> &operator-=(ngn::Vec2<T> &left, const T &right)
{
	left = left - right;
	return left;
}