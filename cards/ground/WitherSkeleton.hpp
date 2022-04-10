#pragma once

struct engine::cards::WitherSkeleton : public virtual engine::ACard
{
	std::string CardName = "WitherSkeleton";
	inline const static ACard::Types CardType = Types::Ground;
	explicit WitherSkeleton(const Vec2u &window_size);
	int getDamage() const;
	int getHealth() const;
	int getCost() const;
private:
	int Damage; // temporary
	int Health; // temporary
	int Cost;
	virtual void movement() final override;
	virtual void onUse() final override;
};

engine::cards::WitherSkeleton::WitherSkeleton(const Vec2u &window_size)
	: ACard(window_size)
{
	if (!texture->loadFromFile("images\\witherskeleton.jpg")) // loading and checking texture
	{
		std::cout << "\nwitherskeleton.jpg was not loaded\n";
		throw;
	}
	Json js = load(CardType);
	Cost = js[CardName][CostStr];
	Damage = js[CardName][DamageStr];
	Health = js[CardName][HealthStr];
	Description = js[CardName][DescriptionStr];
	cover.setTexture(texture);
}

int engine::cards::WitherSkeleton::getDamage() const
{
	return Damage;
}

int engine::cards::WitherSkeleton::getHealth() const
{
	return Health;
}

int engine::cards::WitherSkeleton::getCost() const
{
	return Cost;
}

void engine::cards::WitherSkeleton::onUse()
{
	
}
void engine::cards::WitherSkeleton::movement()
{

}


