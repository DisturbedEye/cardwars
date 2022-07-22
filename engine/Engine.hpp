#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <cmath>
#include <list>
#include <typeinfo>
#include <algorithm>
#include <map>
#include <string>
#include <random>
#include <nlohmann/json.hpp>
#include <exception>


namespace engine
{
	using namespace std::string_literals;
	template <class T> using Vec2 = sf::Vector2<T>;
	template <class T> using Vec3 = sf::Vector3<T>;

	using Vec3i = Vec3<int>;
	using Vec3u = Vec3<unsigned int>;
	using Vec3d = Vec3<double>;
	using Vec3f = Vec3<float>;

	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;
	using Vec2d = Vec2<double>;
	using Vec2f = Vec2<float>;

	using Rect = sf::RectangleShape;
	using Circle = sf::CircleShape;
	using Json = nlohmann::json;
	using Convex = sf::ConvexShape; // convex polygon
	enum class ScrollType
	{
		Vertical, Horizontal
	};
	class JsonFile;
	
	// Input Actions

	class Curve; // Bezier Curve

	struct Clickable;
	
	class ClickableObject;
	class ShaderTexture;
	class Table;
	struct Button;
	struct random;
	template<class>
	class clip;
	template<class Shape, ScrollType ScType = ScrollType::Vertical>
	class Slider;
	template <class T, const ScrollType ScType = ScrollType::Vertical>
	class Scrollable;
	//    cards    //
	class CardTexture;
	/////////////////
	namespace math
	{
		constexpr float pi = 3.14159265f;
		constexpr float rad = pi / 180; // radian
		float time(); // current time after start program
		bool contains(const Rect &rect, const Vec2f &point); // if point in rect, then returns true 
		bool contains(const sf::FloatRect &rect, const Vec2f &point); // ro - left top point of rect
		bool contains(const Convex &polygon, const Vec2f &point);
		bool contains(const Circle &circle, const Vec2f &point);
		float length(const Vec2f &v);
		float length(const float &x, const float &y = 0);
		float around(const float &x, int n); // rounds to n'th number after the decimal point
		inline float sgn(float x) { return x == 0.f ? 0.f : x / abs(x); } // returns a sign of number
		bool belongs(const float &x, const float &m, const float &n);
		inline Vec2f norm(const Vec2f &v) { return v / length(v); }
		sf::Color mix(const sf::Color &c1, const sf::Color &c2);
		float clamp(const float &x, const float &minX, float maxX);
		
	}
	namespace algorithm
	{
		template<class T>
		bool in(const T &value, const std::vector<T> &values);
	}

	
}
namespace emath = engine::math;
namespace ngn = engine;
#include "source.hpp"
#include "Math/math.hpp"
#include "algorithm.hpp"
#include "Table.hpp"
#include "Random.hpp"
#include "Files/FileManagement.hpp"
#include "Curve.hpp"
#include "Texturing/clip.hpp"
#include "Texturing/ShaderTexture.hpp"
#include "Texturing/CardTexture.hpp"
#include "Buttons/Clickable.hpp"
#include "Buttons/button.hpp"
#include "Buttons/Scrollable.hpp"