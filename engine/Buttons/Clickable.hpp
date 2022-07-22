#pragma once
namespace engine
{
	struct Clickable
	{
		virtual ~Clickable() = default;
		/*
		 * keydown: happens when the key is downed.
		 * keyup: happens when the key is released.
		 */
		static bool isKeydown(sf::Event::EventType eventtype) // mouse
		{
			if (eventtype == sf::Event::MouseButtonPressed && !isKeyup(eventtype))
			{
				return true;
			}
			if (eventtype == sf::Event::KeyPressed && !isKeyup(eventtype))
			{
				return true;
			}
			return false;
		}
		static bool isKeyup(sf::Event::EventType eventtype)
		{
			if (eventtype == sf::Event::MouseButtonReleased)
				return true;
			if (eventtype == sf::Event::KeyReleased)
				return true;
			return false;
		}

	};
	class ClickableObject : Clickable
	{
		bool is_pushed = false;
	public:
		bool isKeyup(sf::Event::EventType eventtype, const Vec2f &where)
		{
			return isIntersected(where) and Clickable::isKeyup(eventtype);
		}
		bool isKeydown(sf::Event::EventType eventtype, const Vec2f &where)
		{
			return isIntersected(where) and Clickable::isKeydown(eventtype);
		}
		void push(sf::Event::EventType eventtype, const Vec2f &where)
		{ // if key is down and while not key is up returns true 
			if (isKeydown(eventtype, where))
				is_pushed = true;
			if (Clickable::isKeyup(eventtype))
				is_pushed = false;
		}
		bool isPushed() const { return is_pushed; }
		virtual bool isIntersected(const Vec2f &p) const = 0;
	};
}