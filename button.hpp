#pragma once

struct engine::Button : public sf::Drawable
{
	Button(const Vec2f&, const sf::String&, const sf::Font&, const unsigned int &char_size);
	Button(const Button &b) : content(b.content), rect(b.rect) {}
	Button() { rect = Rect(); content = sf::Text(); }
	void setPosition(const Vec2f position);
	void setOrigin(const Vec2f origin);
	void setScale(const Vec2f scale);
	void setString(const sf::String &string);
	void setIndents(const float&, const float&); // left, top
	void setIndents(const Vec2f&);
	void setShapeSize(const Vec2f&);
	void setSize(const Vec2f&); // size
	void setOutlineColor(const sf::Color&); // outline color
	void setOutlineThickness(const float &thickness); // thickness
	void setColor(const sf::Color&);	// color 
	void setFontColor(const sf::Color&); // font color 
	void setStyle(sf::Uint32 style); // font style
	void setLetterSpacing(float spacingFactor); // letter space 
	void setLineSpacing(float spacingFactor); // line space
	void setCharacterSize(const unsigned int size); // charsize
	void setFontOutline(const float&, const sf::Color&);
	void setTexture(sf::Texture *texture); // texturing 
	void Centralize(const bool&);
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
	bool isPressed(sf::Keyboard::Key);
	bool isPressed(sf::Mouse::Button, const Vec2f &);
	bool isClicked(sf::Keyboard::Key);
	bool isClicked(sf::Mouse::Button, const Vec2f &p);
	bool isIntersected(const Vec2f &p) const;
	bool isHold(const bool &after, const Vec2f &p) const;
private:
	Rect rect;
	sf::Text content;
	Vec2f indents = Vec2f();
	Vec2f defaultIndent;
	bool center = true;
	bool before = false;
	void resetToCenter();
	void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
};



engine::Button::Button(const Vec2f &size, const sf::String &string, const sf::Font &font, const unsigned int &char_size)
{
	rect = Rect(size);
	content = sf::Text(string, font, char_size);
	resetToCenter();
}


inline void engine::Button::setPosition(const Vec2f position)
{
	rect.setPosition(position);
	content.setPosition(position);
}


inline void engine::Button::setOrigin(const Vec2f origin)
{
	rect.setOrigin(origin);
	content.setOrigin(origin);
}


inline void engine::Button::setScale(const Vec2f scale)
{
	rect.setScale(scale);
	content.setScale(scale);
}

inline void engine::Button::setString(const sf::String &string)
{
	/*
	* sets a string to content, 
	* with reseting to center 
	*/
	content.setString(string);
	if (center)
		resetToCenter();
}

inline void engine::Button::setIndents(const float &left, const float &top)
{
	indents = Vec2f(left, top);
	content.setOrigin(defaultIndent + indents);
}

inline void engine::Button::setIndents(const Vec2f &indents)
{
	this->indents = Vec2f(indents);
	content.setOrigin(defaultIndent + indents);
}

inline void engine::Button::setShapeSize(const Vec2f &size)
{
	rect.setSize(size);
}

inline void engine::Button::setSize(const Vec2f &size)
{
	rect.setSize(size);
	if (center)
		resetToCenter();
}

inline void engine::Button::setOutlineColor(const sf::Color &clr)
{
	rect.setOutlineColor(clr);
}

inline void engine::Button::setOutlineThickness(const float &thickness)
{
	rect.setOutlineThickness(thickness);
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
	if (center)
		resetToCenter();
}

inline void engine::Button::setLetterSpacing(float spacingFactor)
{
	content.setLetterSpacing(spacingFactor);
	if (center)
		resetToCenter();
}

inline void engine::Button::setLineSpacing(float spacingFactor)
{
	content.setLineSpacing(spacingFactor);
	if (center)
		resetToCenter();
}

inline void engine::Button::setCharacterSize(const unsigned int size)
{
	content.setCharacterSize(size);
	if (center)
		resetToCenter();
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


inline bool engine::Button::isPressed(sf::Keyboard::Key key) 
{
	const bool after = sf::Keyboard::isKeyPressed(key);
	const bool out = before and !after;
	before = after;
	return out;
}

inline bool engine::Button::isPressed(sf::Mouse::Button button, const Vec2f &p) 
{
	const bool after = sf::Mouse::isButtonPressed(button);
	const bool out = this->isIntersected(p) and before and !after;
	before = after;
	return out;
}


inline bool engine::Button::isClicked(sf::Keyboard::Key key)
{
	const bool after = sf::Keyboard::isKeyPressed(key);
	const bool out = !before and after;
	before = after;
	return out;
}

inline bool engine::Button::isClicked(sf::Mouse::Button button, const Vec2f &p) 
{
	const bool after = sf::Mouse::isButtonPressed(button);
	const bool out = this->isIntersected(p) and !before and after;
	before = after;
	return out;
}


inline bool engine::Button::isIntersected(const Vec2f &p) const
{
	return math::inside(p, rect);
}


inline bool engine::Button::isHold(const bool &after, const Vec2f &p) const
{
	return this->isIntersected(p) and after;
}

inline void engine::Button::resetToCenter()
{
	float x = (content.getGlobalBounds().width - rect.getGlobalBounds().width) / 2.f;
	float y = 0.f;
	defaultIndent = Vec2f(x, y);
	content.setOrigin(defaultIndent);
}


inline void engine::Button::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(rect);
	if (content.getFont() != 0)
		window.draw(content);
}
