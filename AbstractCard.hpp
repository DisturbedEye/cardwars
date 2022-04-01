#pragma once

class engine::AbstractCard : public sf::Drawable
{
public:
	friend class Deck;
	friend class CardSorter;
	virtual void use() const = 0;
	bool isTaked() const;
	bool isChoosed() const; // event when need to see the description
	void onTake();
protected:
	sf::String title;
	sf::String description;
	sf::String type;
	Button<Rect> c;
	Rect cover;
	void setPosition(const Vec2f p);
	void setOrigin(const Vec2f o);
	void setSize(const Vec2f s);
	void setScale(const Vec2f sc);
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
};

void engine::AbstractCard::setPosition(const Vec2f p)
{
	cover.setPosition(p);
}
void engine::AbstractCard::setOrigin(const Vec2f o)
{
	cover.setOrigin(o);
}
void engine::AbstractCard::setSize(const Vec2f s)
{
	cover.setSize(s);
}
void engine::AbstractCard::setScale(const Vec2f sc)
{
	cover.setScale(sc);
}

void engine::AbstractCard::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(cover);
}