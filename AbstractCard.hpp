#pragma once

struct engine::ACard : public sf::Drawable
{
	friend class Deck;
	friend class ACollection;
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
	Rect cover;
	void setPosition(const Vec2f p);
	void setOrigin(const Vec2f o);
	void setSize(const Vec2f s);
	void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
};


engine::ACard::ACard(const Vec2f &window_size)
{
	cover = Rect(Vec2f(window_size.x/9.f, window_size.y/4.f));
}


bool engine::ACard::isChoosed() const
{
	return false;
}
bool engine::ACard::isTaked()
{
	return false;
}
void engine::ACard::onTake()
{

}
void engine::ACard::setPosition(const Vec2f p)
{
	cover.setPosition(p);
}
void engine::ACard::setOrigin(const Vec2f o)
{
	cover.setOrigin(o);
}
void engine::ACard::setSize(const Vec2f s)
{
	cover.setSize(s);
}
void engine::ACard::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(cover);
}