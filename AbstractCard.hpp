#pragma once

struct engine::ACollection::ACard : public sf::Drawable
{
	friend class Deck;
	friend class AbstractCollection;
	enum class Types
	{
		Ground, Air, Debuff, Buff, Water, Static
	};
	
	virtual void onUse() const = 0;
	bool isTaked();
	bool isChoosed() const; // event when need to see the description
	void onTake();
protected:
	ACard(const Vec2f &window_size);
	Button<Rect> card_collision;
	Rect cover;
	void setPosition(const Vec2f p);
	void setOrigin(const Vec2f o);
	void setSize(const Vec2f s);
	void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
};


engine::ACollection::ACard::ACard(const Vec2f &window_size)
{
	cover = Rect(Vec2f(window_size.x/9.f, window_size.y/4.f));
	card_collision = Button<Rect>(cover);
}


bool engine::ACollection::ACard::isChoosed() const
{
	return false;
}
bool engine::ACollection::ACard::isTaked()
{
	return false;
}
void engine::ACollection::ACard::onTake()
{

}
void engine::ACollection::ACard::setPosition(const Vec2f p)
{
	cover.setPosition(p);
}
void engine::ACollection::ACard::setOrigin(const Vec2f o)
{
	cover.setOrigin(o);
}
void engine::ACollection::ACard::setSize(const Vec2f s)
{
	cover.setSize(s);
}
void engine::ACollection::ACard::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(cover);
}