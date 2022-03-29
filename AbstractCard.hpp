#pragma once

class engine::AbstractCard
{
public:

private:
	sf::String title;
	sf::Texture cover;
	friend Deck;
	virtual void setPosition(const Vec2f p);
};