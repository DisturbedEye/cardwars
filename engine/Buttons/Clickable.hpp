#pragma once
namespace engine
{
	struct engine::Clickable
	{
		virtual ~Clickable() = default;
		bool isClicked(sf::Mouse::Button b) const
		{
			const bool after = sf::Mouse::isButtonPressed(b);
			const bool out = !beforem and after;
			const_cast<bool&>(beforem) = after;
			return out;
		}
		bool isPressed(sf::Mouse::Button b) const
		{
			const bool after = sf::Mouse::isButtonPressed(b);
			const bool out = beforem and !after;
			const_cast<bool &>(beforem) = after;
			return out;
		}
		bool isPressed(sf::Keyboard::Key k) const
		{
			const bool after = sf::Keyboard::isKeyPressed(k);
			const bool out = beforek and !after;
			const_cast<bool &>(beforek) = after;
			return out;
		}
		bool isClicked(sf::Keyboard::Key k) const
		{
			const bool after = sf::Keyboard::isKeyPressed(k);
			const bool out = !beforek and after;
			const_cast<bool &>(beforek) = after;
			return out;
		}
		bool isHold(sf::Mouse::Button b) const
		{
			const bool after = sf::Mouse::isButtonPressed(b);
			const bool out = beforem and after;
			const_cast<bool &>(beforem) = after;
			return out;
		}
		bool isHold(sf::Keyboard::Key k) const
		{
			const bool after = sf::Keyboard::isKeyPressed(k);
			const bool out = beforek and after;
			const_cast<bool &>(beforek) = after;
			return out;
		}
		bool isPressed(sf::Mouse::Button b, const Vec2f &p) const 
		{
			const bool after = sf::Mouse::isButtonPressed(b);
			const bool out = this->isIntersected(p) and beforem and !after;
			const_cast<bool &>(beforem) = after;
			return out;
		}
		bool isClicked(sf::Mouse::Button b, const Vec2f &p) const
		{
			/// <summary>
			///  returns true if was pressed previous and wasn't pressed current time 
			/// </summary>
			/// <param name="b">mouse button</param>
			/// <param name="p">point when hold</param>
			const bool after = sf::Mouse::isButtonPressed(b);
			const bool out = this->isIntersected(p) and !beforem and after;
			const_cast<bool &>(beforem) = after;
			return out;
		}
		bool isHold(sf::Mouse::Button b, const Vec2f &p) const
		{
			/// <summary>
			///  returns true if was pressed previous and current time 
			/// </summary>
			/// <param name="b">mouse button</param>
			/// <param name="p">point when hold</param>
			const bool after = sf::Mouse::isButtonPressed(b);
			const bool out = this->isIntersected(p) and beforem and after;
			const_cast<bool &>(beforem) = after;
			return out;
		}
		virtual bool isIntersected(const Vec2f &p) const = 0;
	private:
		bool beforek = false; // for keyboard
		bool beforem = false; // for mouse
	};

	template<class Shape>
	class engine::ClickableShape : public Clickable
	{
	protected:
		Shape shape;
	public:
		ClickableShape(Shape sh) : shape(sh) {}
		ClickableShape() = default;
		bool isIntersected(const Vec2f &p) const override { return math::contains(shape, p); }
	};
	template<class Shape>
	class engine::ClickableShape<Shape*> : public Clickable
	{
	protected:
		Shape *shape;
	public:
		ClickableShape(Shape *sh) : shape(sh) {}
		ClickableShape() = default;
		bool isIntersected(const Vec2f &p) const override {return math::contains(*shape, p);}
	};
}