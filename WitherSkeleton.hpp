#pragma once

struct engine::cards::WitherSkeleton : public virtual engine::ACard
{
	inline const static int Damage = 2; // temporary
	inline const static int Health = 4; // temporary
	inline const static int Cost = 3;
	inline const static std::string fway = "src/cards";
	inline const static std::string fname = "witherskeleton";
	inline const static ACard::Types CardType = Types::Ground;
	explicit WitherSkeleton(const Vec2f &window_size);
private:
	virtual void onUse() const final override;
};

engine::cards::WitherSkeleton::WitherSkeleton(const Vec2f &window_size)
	: ACard(window_size)
{
	sf::Texture texture;
	if (!texture.loadFromFile("images\\witherskeleton.jpg"))
	{
		std::cout << "\nwitherskeleton.jpg was not loaded\n";
		throw;
	}
	cover.setTexture(&texture);
}

void engine::cards::WitherSkeleton::onUse() const
{
	
}


