#pragma once

struct engine::AbstractCard : public sf::Drawable
{
	friend class Deck;
	enum class Type
	{
		Ground, Air, Debuff, Buff, Water, Static
	};
	AbstractCard(const Vec2f &window_size);
	AbstractCard() {}
	virtual void onUse() const = 0;
	bool isTaked();
	bool isChoosed() const; // event when need to see the description
	void onTake();
protected:
	Button<Rect> card_collision;
	Rect cover;
	void setPosition(const Vec2f p);
	void setOrigin(const Vec2f o);
	void setSize(const Vec2f s);
	void setScale(const Vec2f sc);
	virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
};


engine::AbstractCard::AbstractCard(const Vec2f &window_size)
{
	cover = Rect(Vec2f(window_size.x/9.f, window_size.y/4.f));
	card_collision = Button<Rect>(cover);
}


bool engine::AbstractCard::isChoosed() const
{
	return false;
}
bool engine::AbstractCard::isTaked()
{
}
void engine::AbstractCard::onTake()
{

}
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