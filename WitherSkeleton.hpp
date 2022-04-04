#pragma once

struct engine::ACollection::WitherSkeleton : public virtual engine::ACollection::ACard
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

engine::ACollection::WitherSkeleton::WitherSkeleton(const Vec2f &window_size)
	: ACard(window_size)
{
	sf::Texture texture;
	if (!texture.loadFromFile("images\\witherskeleton.jpg"))
	{
		std::cout << "\nwitherskeleton.jpg was not loaded";
		throw;
	}
	cover.setTexture(&texture);
}

void engine::ACollection::WitherSkeleton::onUse() const
{
	
}


