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
	class Button : public sf::Drawable 
	{
	public:
		Shape shape;
		sf::Text content;

		Button(const Shape shape);
		void waitForAction(const bool &before, const bool &after, const Vec2f &p);
		void setPosition(const Vec2f position);
		void setOrigin(const Vec2f origin);
		bool isPressed() const;
		bool isClicked() const;
		bool isIntersected() const;
		bool isHold() const;
	private:
		virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
		bool is_pressed = false;
		bool is_hold = false;
		bool is_clicked = false;
		bool intersected = false;
	};
	class Deck;
	class AbstractCard;
	namespace math
	{
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
#include "Deck.hpp"