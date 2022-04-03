#pragma once

struct engine::Deck::ACollection::WitherSkeleton : public virtual engine::Deck::ACollection::ACard
{
	inline const static int Damage = 2; // temporary
	inline const static int Health = 4; // temporary
	inline const static int Cost = 3;
	inline const static std::string Name = "Wither Skeleton";
	inline const static std::string Description = "Something";
	inline const static ACard::Types CardType = Types::Ground;
	explicit WitherSkeleton(const Vec2f &window_size);
private:
	virtual void onUse() const final override;
};

engine::Deck::ACollection::WitherSkeleton::WitherSkeleton(const Vec2f &window_size)
	: ACard(window_size)
{
	sf::Texture texture;
	texture.loadFromFile("images\\witherskeleton.jpg");
	cover.setTexture(&texture);
}

void engine::Deck::ACollection::WitherSkeleton::onUse() const
{
	
}


