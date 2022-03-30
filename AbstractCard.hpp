#pragma once

class engine::AbstractCard
{
public:
	friend class Deck;
	friend class CardSorter;
	virtual void onUse() = 0;
	virtual bool isTaked() = 0;
protected:
	sf::String title;
	sf::String description;
	Rect cover;
private:
	virtual void setPosition(const Vec2f p) = 0;
	virtual void setOrigin(const Vec2f o) = 0;
	virtual void setSize(const Vec2f s) = 0;
};