#include <SFML/Graphics.hpp>
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
	using Convex = sf::ConvexShape; // выпуклый многоугольник
	enum class ScrollType
	{
		Vertical, Horizontal
	};
	
	std::vector<int> video_modes = { sf::Style::Close, sf::Style::None, sf::Style::Fullscreen };
	std::map<int, int> reverse_modes = { {video_modes[0], 0}, {video_modes[1], 1}, {video_modes[2], 2} };
	
	class JsonFile;

	inline size_t getVideoModesCount() { return video_modes.size(); }
	// Input Actions
	struct Clickable;
	template<class Shape>
	class ClickableShape;

	using ClickableRect = ClickableShape<Rect>;
	using ClickableConvex = ClickableShape<Convex>;
	using ClickableCircle = ClickableShape<Circle>;
	class ShaderTexture;
	struct Button;
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
		bool contains(const Rect &rect, const Vec2f &point);
		bool contains(const Vec2f &ro, const Vec2f &rs, const Vec2f &point);
		bool contains(const Convex &polygon, const Vec2f &point);
		bool contains(const Circle &circle, const Vec2f &point);
		float length(const Vec2f &v);
		float length(const float &x, const float &y = 0);
		float around(const float &x, int n);
		bool belongs(const float &x, const float &m, const float &n);
		inline Vec2f norm(const Vec2f &v) { return v / length(v); }
		sf::Color mix(const sf::Color &c1, const sf::Color &c2);
		float clamp(const float &x, const float &minX, float maxX);
		template <class T>
		size_t get_index(const std::vector<T> &v, T n);
	}
}
#include "RuneWars.hpp"
namespace rcolls = rune::collections;
namespace rcards = rune::cards;
namespace emath = engine::math;
#include "source.hpp"
#include "emath.hpp"
#include "FileManagement.hpp"
#include "clip.hpp"
#include "ShaderTexture.hpp"
#include "Clickable.hpp"
#include "button.hpp"
#include "Scrollable.hpp"
#include "CardTexture.hpp"
//    cards    //

#include "cards/AbstractCard.hpp"
#include "cards/ground/WitherSkeleton.hpp"
#include "cards/ground/Gladiator.hpp"
// collections //

#include "AbstractCollection.hpp"

#include "SuperCollection.hpp"

/////////////////
#include "Deck.hpp"
#include "Field.hpp"
#include "Player.hpp"