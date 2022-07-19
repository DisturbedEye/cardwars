#pragma once
namespace engine
{
	struct Clickable
	{
		virtual ~Clickable() = default;
		bool isClicked(sf::Mouse::Button what)
		{
			const bool after = sf::Mouse::isButtonPressed(what);
			const bool out = !beforem and after;
			beforem = after;
			return out;
		}
		bool isPressed(sf::Mouse::Button what)
		{
			const bool after = sf::Mouse::isButtonPressed(what);
			const bool out = beforem and !after;
			beforem = after;
			return out;
		}
		bool isPressed(sf::Keyboard::Key what)
		{
			const bool after = sf::Keyboard::isKeyPressed(what);
			const bool out = beforek and !after;
			beforek = after;
			return out;
		}
		bool isClicked(sf::Keyboard::Key what)
		{
			const bool after = sf::Keyboard::isKeyPressed(what);
			const bool out = !beforek and after;
			beforek = after;
			return out;
		}
		bool isHold(sf::Mouse::Button what)
		{
			const bool after = sf::Mouse::isButtonPressed(what);
			const bool out = beforem and after;
			beforem = after;
			return out;
		}
		bool isHold(sf::Keyboard::Key what)
		{
			const bool after = sf::Keyboard::isKeyPressed(what);
			const bool out = beforek and after;
			beforek = after;
			return out;
		}
		bool isPressed(sf::Mouse::Button what, const Vec2f &where)  
		{
			return isIntersected(where) and isPressed(what);
		}
		bool isClicked(sf::Mouse::Button what, const Vec2f &where)
		{
			/// <summary>
			///  returns true if was pressed previous and wasn't pressed current time 
			/// </summary>
			/// <param name="b">mouse button</param>
			/// <param name="p">point when hold</param>
			return isIntersected(where) and isClicked(what);
		}
		bool isHold(sf::Mouse::Button what, const Vec2f &where) 
		{
			/// <summary>
			///  returns true if was pressed previous and current time 
			/// </summary>
			/// <param name="b">mouse button</param>
			/// <param name="p">point when hold</param>
			return isIntersected(where) and isHold(what);
		}
		bool isAttached(sf::Mouse::Button what, const Vec2f &where) // if clicked in <where> and while <what> (button) is hold hold returns true
		{
			/// <summary>
			///  returns true if was pressed previous and current time 
			/// </summary>
			/// <param name="b">mouse button</param>
			/// <param name="p">point when hold</param>

			if (isClicked(what, where))
				beforem = true;
			if (!isHold(what))
				beforem = false;
			return beforem;
		}
		void waitForAction(sf::Mouse::Button what, const Vec2f &where)
		{
			if (isIntersected(where))
			{
				onIntersection();
				if (isClicked(what))
					onClick();
				else if (isHold(what))
					onHold();
				else if (isPressed(what))
					onPress();
			}
			else noIntersection();
		}
		void waitForAction(sf::Keyboard::Key what)
		{
			if (isClicked(what))
			{
				onIntersection();
				onClick();
			}
			else if (isHold(what))
			{
				onIntersection();
				onHold();
			}
			else if (isPressed(what))
			{
				onIntersection();
				onPress();
			}
			else noIntersection();
		}
		virtual void noIntersection() {}
		virtual void onIntersection() {}
		virtual void onHold() {}
		virtual void onClick() {}
		virtual void onPress() {}
		virtual bool isIntersected(const Vec2f &p) const = 0;
	private:
		bool beforek = false; // for keyboard
		bool beforem = false; // for mouse
		//bool a = false;
	};

	template<class Shape>
	class ClickableShape : public Clickable
	{
	protected:
		Shape shape;
	public:
		ClickableShape(Shape sh) : shape(sh) {}
		ClickableShape() = default;
		bool isIntersected(const Vec2f &p) const override { return math::contains(shape, p); }
	};
	template<class Shape>
	class ClickableShape<Shape*> : public Clickable
	{
	protected:
		Shape *shape;
	public:
		ClickableShape(Shape *sh) : shape(sh) {}
		ClickableShape() = default;
		bool isIntersected(const Vec2f &p) const override {return math::contains(*shape, p);}
	};
}