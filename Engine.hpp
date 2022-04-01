#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>

namespace engine
{
	typedef sf::Vector2f Vec2f;
	typedef sf::Vector2i Vec2i;
	typedef sf::Vector2u Vec2u;
	typedef sf::RectangleShape Rect;
	typedef sf::CircleShape Circle;
	typedef sf::ConvexShape Convex; // выпуклый многоугольник
	template <class Shape>
	class Button;
	class Deck;
	class CardSorter;
	class AbstractCard;
	namespace math
	{
		const float pi = 3.14159265f;
		const float rad = pi / 180;
		bool inside(const Vec2f &point, const Rect &rect);
		bool inside(const Vec2f &point, const Vec2f ro, const Vec2f rs);
		float length(const Vec2f &v);
		bool around(const float &x, const int n);
		bool belongs(const float &x, const float &m, const float &n);
		bool inside(const Vec2f &point, const Convex &polygon);
		bool inside(const Vec2f &point, const Circle &circle);
		sf::Color mix(const sf::Color &c1, const sf::Color &c2);
	}
}



#include "emath.hpp"
#include "button.hpp"
#include "AbstractCard.hpp"
// including cards //

#include "WitherSkeleton.hpp"

/////////////////////
#include "CardSorter.hpp"
#include "Deck.hpp"