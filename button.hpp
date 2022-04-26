#pragma once

struct engine::Button : sf::Drawable, Clickable
{
	Button(const Vec2f &, const sf::String &, const sf::Font &, const unsigned int &char_size);
	Button();
	Button(const Button &b) : Clickable(b.rect),
		content(b.content), indents(b.indents),
		center(b.center)
	{
		if (center)
			reset_to_center();
	}
	~Button() override = default;
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

inline engine::Button::Button() : Clickable() {}

inline engine::Button::Button(const Vec2f &size, const sf::String &string, const sf::Font &font, const unsigned int &char_size)
	: Clickable(Rect(size)), content(string, font, char_size)
{
	reset_to_center();
}


inline void engine::Button::setPosition(const Vec2f position)
{
	rect.setPosition(position);
	content.setPosition(position);
	reset_to_center();
}


inline void engine::Button::setOrigin(const Vec2f &origin)
{
	rect.setOrigin(origin);
	reset_to_center();
}


inline void engine::Button::setScale(const Vec2f scale)
{
	rect.setScale(scale);
	content.setScale(scale);
	reset_to_center();
}

inline void engine::Button::setFontScale(Vec2f scale)
{
	content.setScale(scale);
}

inline void engine::Button::setString(const sf::String &string)
{
	/*
	* sets a string to content,
	* with reseting to center
	*/
	content.setString(string);
	reset_to_center();
}

inline void engine::Button::setIndents(const float &left, const float &top)
{
	indents = Vec2f(left, top);
	content.setOrigin(indents);
}

inline void engine::Button::setIndents(const Vec2f &indents)
{
	this->indents = Vec2f(indents);
	content.setOrigin(indents);
}

inline void engine::Button::setShapeSize(const Vec2f &size)
{
	rect.setSize(size);
	reset_to_center();
}

inline void engine::Button::setSize(const Vec2f &size)
{
	rect.setSize(size);
	reset_to_center();
}

inline void engine::Button::setColor(const sf::Color &clr)
{
	rect.setFillColor(clr);
}

inline void engine::Button::setFontColor(const sf::Color &clr)
{
	content.setFillColor(clr);
}

inline void engine::Button::setStyle(sf::Uint32 style)
{
	content.setStyle(style);
	reset_to_center();
}

inline void engine::Button::setLetterSpacing(float spacingFactor)
{
	content.setLetterSpacing(spacingFactor);
	reset_to_center();
}

inline void engine::Button::setLineSpacing(float spacingFactor)
{
	content.setLineSpacing(spacingFactor);
	reset_to_center();
}

inline void engine::Button::setCharacterSize(const unsigned int size)
{
	content.setCharacterSize(size);
	reset_to_center();
}

inline void engine::Button::setFontOutline(const float &t, const sf::Color &clr)
{
	content.setOutlineThickness(t);
	content.setOutlineColor(clr);
}

inline void engine::Button::setTexture(sf::Texture *texture)
{
	rect.setTexture(texture);
}

inline void engine::Button::Centralize(const bool &b)
{
	center = b;
}

inline sf::Vector2f engine::Button::getIndents() const
{
	return indents;
}

inline sf::FloatRect engine::Button::getTextGlobalBounds() const
{
	return content.getGlobalBounds();
}

inline sf::FloatRect engine::Button::getShapeGlobalBounds() const
{
	return rect.getGlobalBounds();
}

inline sf::FloatRect engine::Button::getTextLocalBounds() const
{
	return content.getLocalBounds();
}

inline sf::FloatRect engine::Button::getShapeLocalBounds() const
{
	return rect.getLocalBounds();
}

inline sf::Vector2f engine::Button::getSize() const
{
	return rect.getSize();
}

inline sf::Color engine::Button::getOutLineColor() const
{
	return rect.getOutlineColor();
}

inline float engine::Button::getOutLineThickness() const
{
	return rect.getOutlineThickness();
}

inline sf::Color engine::Button::getColor() const
{
	return rect.getFillColor();
}

inline sf::Color engine::Button::getFontColor() const
{
	return content.getFillColor();
}

inline sf::Uint32 engine::Button::getStyle() const
{
	return content.getStyle();
}

inline float engine::Button::getLetterSpacing() const
{
	return content.getLetterSpacing();
}

inline float engine::Button::getLineSpacing() const
{
	return content.getLineSpacing();
}

inline unsigned int engine::Button::getCharacterSize() const
{
	return content.getCharacterSize();
}

inline sf::Color engine::Button::getFontOutlineColor() const
{
	return content.getOutlineColor();
}

inline float engine::Button::getFontOutlineThickness() const
{
	return content.getOutlineThickness();
}


inline void engine::Button::reset_to_center()
{
	float w = (rect.getGlobalBounds().width - content.getGlobalBounds().width) / 2.f;
	float h = (rect.getGlobalBounds().height - content.getGlobalBounds().height) / 2.f;
	Vec2f p = Vec2f(content.getGlobalBounds().left, content.getGlobalBounds().top) - content.getPosition();
	Vec2f defaultIndent = Vec2f(w, h);
	content.setPosition(rect.getPosition() + defaultIndent - p);
}


inline void engine::Button::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(rect);
	window.draw(content);
}