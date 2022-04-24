#pragma once

class engine::Deck : public sf::Drawable
{
public:
	explicit Deck(ACollection *col, int card_count_by_width, const Vec2f &indents, const float &height);
	void shuffle() const; // shuffle deck
	void setPosition(const Vec2f &p);
	void setSize(unsigned int card_count_by_width, const Vec2f &indents, const float &height);
	void setOrigin(const Vec2f &_or) { origin = _or; }
	Vec2f getOrigin() const { return origin; }
	void setSliderPos(const float &y);
	void setPosition(const float &x, const float &y);
	void setWidthIndent(const float &indent);
	void setHeightIndent(const float &indent);
	void setSliderThickness(const float &thickness) { slider.setSize(Vec2f(thickness, slider.getSize().y)); }
	void setSliderFillColor(const sf::Color &clr) { slider.setFillColor(clr); }
	void setSliderOutlineColor(const sf::Color &clr) { slider.setOutlineColor(clr); }
	void setSliderOutlineThickness(const float &thickness) { slider.setOutlineThickness(thickness); }
	bool sliderIsClicked(sf::Mouse::Button b, const Vec2f &p) { return slider.isClicked(b, p); }
	bool sliderIsPressed(sf::Mouse::Button b, const Vec2f &p) { return slider.isPressed(b, p); }
	bool sliderIsHold(sf::Mouse::Button b, const Vec2f &p) { return slider.isHold(b, p); }
	bool sliderIsClicked(sf::Mouse::Button b) { return slider.isClicked(b); }
	bool sliderIsPressed(sf::Mouse::Button b) { return slider.isPressed(b); }
	bool sliderIsHold(sf::Mouse::Button b) { return slider.isHold(b); }
	Vec2f getPosition() const { return position; }
	Vec2f getSize() const { return size; }
	Vec2f getSliderPos() const { return slider.getPosition(); }
	Vec2f getSliderSize() const { return slider.getSize(); }
	sf::Color getSliderFillColor() const { return slider.getFillColor(); }
	sf::Color getSliderOutlineColor() const { return slider.getOutlineColor(); }
	float getSliderOutlineThickness() const { return slider.getOutlineThickness(); }
	sf::FloatRect getLocalBounds() const { return sf::FloatRect(position, size); }
	sf::FloatRect getGlobalBounds() const { return sf::FloatRect(position, Vec2f(size.x + slider.getSize().x, size.y)); }
private:
	Vec2f position; // deck position
	Vec2f origin;
	Vec2f size; // deck size
	Vec2f ind; // indents
	Slider slider;
	Vec2u n; // card count by width, height
	Vec2f cs; // card size
	ACollection *collection;
	void recount_slider_atr();
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override;
};

inline void engine::Deck::shuffle() const
{
	srand(static_cast<unsigned int>(std::time(NULL)));
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(collection->cards.begin(), collection->cards.end(), generator);
}

inline engine::Deck::Deck(ACollection *col, int card_count_by_width, const Vec2f &indents, const float &height)
	: position(0, 0), collection(col)
{
	cs = collection->getCardSize();
	setSize(card_count_by_width, indents, height);
}

inline void engine::Deck::setSliderPos(const float &y)
{
	slider.setPosition(slider.getPosition().x, y);
}

inline void engine::Deck::setPosition(const Vec2f &p)
{
	position = p;
	recount_slider_atr();
}

inline void engine::Deck::setPosition(const float &x, const float &y)
{
	setPosition(Vec2f(x, y));
}

inline void engine::Deck::setWidthIndent(const float &indent)
{
	ind.x = abs(indent);
	recount_slider_atr();
}

inline void engine::Deck::setHeightIndent(const float &indent)
{
	ind.y = abs(indent);
	recount_slider_atr();
}

inline void engine::Deck::setSize(unsigned int card_count_by_width, const Vec2f &indents, const float &height)
{
	if (card_count_by_width == 0 or height == 0)
	{
		std::cerr << "card count by width and height can't equal zero";
		throw;
	}
	const size_t card_count = collection->size();
	ind = indents;
	n.x = card_count_by_width;
	n.y = static_cast<int>(ceil(card_count / n.x))+1;
	ind = indents;
	size.x = n.x*(cs.x + ind.x);
	size.y = height;
	recount_slider_atr();
}

inline void engine::Deck::recount_slider_atr()
{
	const Vec2f sls = Vec2f(size.x/30, powf(size.y, 2)/(n.y*(cs.y + ind.y))); // slider size
	slider.setSize(sls);
	if (slider.getSize().y >= size.y)
		slider.setPosition(position.x + n.x * (cs.x + ind.x), position.y);
	else 
		slider.setPosition(position.x + n.x * (cs.x + ind.x), slider.getPosition().y);
	slider.setLimit(position.y, position.y + size.y - sls.y);
}


inline void engine::Deck::draw(sf::RenderTarget &win, sf::RenderStates st) const
{
	const float t = (slider.getPosition().y - position.y) / size.y;

	for (size_t i = 0; i < collection->size(); i++)
	{
		const int x = static_cast<int>(i) % n.x, y = static_cast<int>(floor(i / n.x));
		const float x1 = position.x + x * (cs.x + ind.x), y1 = position.y + (cs.y + ind.y) * (y - t * n.y);
		(*collection)[i]->setPosition(x1, y1);
		if (math::inside(Vec2f(x1, y1), position, size) or
			math::inside(Vec2f(x1, y1 + collection->getCardSize().y), position, size))
			win.draw(*(*collection)[i]);
	}
	if (slider.getSize().y < size.y)
		win.draw(slider);
}