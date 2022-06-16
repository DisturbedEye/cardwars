#pragma once
namespace engine
{
	struct Button : Rect, Clickable
	{
		Button(const Rect &, const sf::String &, const sf::Font &);
		Button(const Vec2f &, const sf::String &, const sf::Font &);
		Button() = default;
		void setPosition(Vec2f position);
		void setPosition(const float &x, const float &y) { setPosition(Vec2f(x, y)); }
		void setOrigin(const Vec2f &origin);
		void setOrigin(const float &x, const float &y) { setOrigin(Vec2f(x, y)); }
		void setScale(Vec2f scale);
		void setScale(const float &x, const float &y) { setScale(Vec2f(x, y)); }
		void setIndents(const float &, const float &); // top, left, down, right 
		void setIndents(const Vec2f &);
		void setSize(const Vec2f &sz);
		Vec2f getIndents() const; // left, top
		bool isIntersected(const Vec2f& p) const override
		{
			return math::contains(Rect(*this), p);
		}
		sf::Text content;
	private:
		Vec2f indents = Vec2f();
		void reset_to_center();
		void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
	};

	inline Button::Button(const Rect &rect, const sf::String &string, const sf::Font &font)
		: content(string, font)
	{
		setSize(rect.getSize());
		reset_to_center();
	}
	inline Button::Button(const Vec2f &size, const sf::String &string, const sf::Font &font)
		: content(string, font)
	{
		setSize(size);
		reset_to_center();
	}

	inline void Button::setPosition(const Vec2f position)
	{
		Rect::setPosition(position);
		reset_to_center();
	}


	inline void Button::setOrigin(const Vec2f &origin)
	{
		Rect::setOrigin(origin);
		reset_to_center();
	}


	inline void Button::setScale(const Vec2f scale)
	{
		Rect::setScale(scale);
		reset_to_center();
	}
	

	inline void Button::setIndents(const float &left, const float &top)
	{
		indents = Vec2f(left, top);
		content.setOrigin(indents);
	}

	inline void Button::setIndents(const Vec2f &indents)
	{
		this->indents = Vec2f(indents);
		content.setOrigin(indents);
	}

	inline void Button::setSize(const Vec2f &size)
	{
		Rect::setSize(size);
		content.setCharacterSize(static_cast<unsigned>(3.f / 6.f * getSize().y));
		reset_to_center();
	}

	inline sf::Vector2f Button::getIndents() const
	{
		return indents;
	}
	

	inline void Button::reset_to_center()
	{
		float w = (getGlobalBounds().width - content.getGlobalBounds().width) / 2.f;
		float h = (getGlobalBounds().height - content.getGlobalBounds().height) / 2.f;
		Vec2f p = Vec2f(content.getGlobalBounds().left, content.getGlobalBounds().top) - content.getPosition();
		Vec2f defaultIndent = Vec2f(w, h);
		content.setPosition(getPosition() + defaultIndent - p);
	}


	inline void Button::draw(sf::RenderTarget &window, sf::RenderStates states) const
	{
		window.draw(Rect(*this), states);
		window.draw(content, states);
	}
}