#pragma once
namespace engine
{
	struct Button : ClickableRect, sf::Drawable
	{
		Button(const Rect &, const sf::String &, const sf::Font &, const unsigned &char_size = 38u);
		Button(const Vec2f &, const sf::String &, const sf::Font &, const unsigned &char_size = 38u);
		Button() = default;
		void setPosition(Vec2f position);
		void setPosition(const float &x, const float &y) { setPosition(Vec2f(x, y)); }
		void setOrigin(const Vec2f &origin);
		void setScale(Vec2f scale);
		void setFontScale(Vec2f scale);
		void setString(const sf::String &string);
		void setIndents(const float &, const float &); // top, left, down, right 
		void setIndents(const Vec2f &);
		void setShapeSize(const Vec2f &);
		void setSize(const Vec2f &); // size
		void setColor(const sf::Color &); // color 
		void setFontColor(const sf::Color &); // font color 
		void setStyle(sf::Uint32 style); // font style
		void setLetterSpacing(float spacingFactor); // letter space 
		void setLineSpacing(float spacingFactor); // line space
		void setCharacterSize(unsigned int size); // charsize
		void setFontOutline(const float &, const sf::Color &);
		void setTexture(sf::Texture *texture); // texturing 
		void Centralize(const bool &);
		Vec2f getIndents() const; // left, top
		sf::FloatRect getTextGlobalBounds() const;
		sf::FloatRect getShapeGlobalBounds() const;
		sf::FloatRect getTextLocalBounds() const;
		sf::FloatRect getShapeLocalBounds() const;
		Vec2f getSize() const;
		sf::Color getOutLineColor() const;
		float getOutLineThickness() const;
		sf::Color getColor() const;
		sf::Color getFontColor() const;
		sf::Uint32 getStyle() const;
		float getLetterSpacing() const;
		float getLineSpacing() const;
		unsigned int getCharacterSize() const;
		sf::Color getFontOutlineColor() const;
		float getFontOutlineThickness() const;
	private:
		sf::Text content;
		Vec2f indents = Vec2f();
		bool center = true;
		void reset_to_center();
		void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
	};

	inline Button::Button(const Rect &rect, const sf::String &string, const sf::Font &font, const unsigned &char_size)
		: ClickableRect(rect), content(string, font, char_size)
	{
		reset_to_center();
	}
	inline Button::Button(const Vec2f &size, const sf::String &string, const sf::Font &font, const unsigned &char_size)
		: ClickableRect(Rect(size)), content(string, font, char_size)
	{
		reset_to_center();
	}

	inline void Button::setPosition(const Vec2f position)
	{
		shape.setPosition(position);
		content.setPosition(position);
		reset_to_center();
	}


	inline void Button::setOrigin(const Vec2f &origin)
	{
		shape.setOrigin(origin);
		reset_to_center();
	}


	inline void Button::setScale(const Vec2f scale)
	{
		shape.setScale(scale);
		content.setScale(scale);
		reset_to_center();
	}

	inline void Button::setFontScale(Vec2f scale)
	{
		content.setScale(scale);
	}

	inline void Button::setString(const sf::String &string)
	{
		/*
		* sets a string to content,
		* with reseting to center
		*/
		content.setString(string);
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

	inline void Button::setShapeSize(const Vec2f &size)
	{
		shape.setSize(size);
		reset_to_center();
	}

	inline void Button::setSize(const Vec2f &size)
	{
		shape.setSize(size);
		reset_to_center();
	}

	inline void Button::setColor(const sf::Color &clr)
	{
		shape.setFillColor(clr);
	}

	inline void Button::setFontColor(const sf::Color &clr)
	{
		content.setFillColor(clr);
	}

	inline void Button::setStyle(sf::Uint32 style)
	{
		content.setStyle(style);
		reset_to_center();
	}

	inline void Button::setLetterSpacing(float spacingFactor)
	{
		content.setLetterSpacing(spacingFactor);
		reset_to_center();
	}

	inline void Button::setLineSpacing(float spacingFactor)
	{
		content.setLineSpacing(spacingFactor);
		reset_to_center();
	}

	inline void Button::setCharacterSize(const unsigned int size)
	{
		content.setCharacterSize(size);
		reset_to_center();
	}

	inline void Button::setFontOutline(const float &t, const sf::Color &clr)
	{
		content.setOutlineThickness(t);
		content.setOutlineColor(clr);
	}

	inline void Button::setTexture(sf::Texture *texture)
	{
		shape.setTexture(texture);
	}

	inline void Button::Centralize(const bool &b)
	{
		center = b;
	}

	inline sf::Vector2f Button::getIndents() const
	{
		return indents;
	}

	inline sf::FloatRect Button::getTextGlobalBounds() const
	{
		return content.getGlobalBounds();
	}

	inline sf::FloatRect Button::getShapeGlobalBounds() const
	{
		return shape.getGlobalBounds();
	}

	inline sf::FloatRect Button::getTextLocalBounds() const
	{
		return content.getLocalBounds();
	}

	inline sf::FloatRect Button::getShapeLocalBounds() const
	{
		return shape.getLocalBounds();
	}

	inline sf::Vector2f Button::getSize() const
	{
		return shape.getSize();
	}

	inline sf::Color Button::getOutLineColor() const
	{
		return shape.getOutlineColor();
	}

	inline float Button::getOutLineThickness() const
	{
		return shape.getOutlineThickness();
	}

	inline sf::Color Button::getColor() const
	{
		return shape.getFillColor();
	}

	inline sf::Color Button::getFontColor() const
	{
		return content.getFillColor();
	}

	inline sf::Uint32 Button::getStyle() const
	{
		return content.getStyle();
	}

	inline float Button::getLetterSpacing() const
	{
		return content.getLetterSpacing();
	}

	inline float Button::getLineSpacing() const
	{
		return content.getLineSpacing();
	}

	inline unsigned int Button::getCharacterSize() const
	{
		return content.getCharacterSize();
	}

	inline sf::Color Button::getFontOutlineColor() const
	{
		return content.getOutlineColor();
	}

	inline float Button::getFontOutlineThickness() const
	{
		return content.getOutlineThickness();
	}


	inline void Button::reset_to_center()
	{
		float w = (shape.getGlobalBounds().width - content.getGlobalBounds().width) / 2.f;
		float h = (shape.getGlobalBounds().height - content.getGlobalBounds().height) / 2.f;
		Vec2f p = Vec2f(content.getGlobalBounds().left, content.getGlobalBounds().top) - content.getPosition();
		Vec2f defaultIndent = Vec2f(w, h);
		content.setPosition(shape.getPosition() + defaultIndent - p);
	}


	inline void Button::draw(sf::RenderTarget &window, sf::RenderStates states) const
	{
		window.draw(shape);
		window.draw(content);
	}
}