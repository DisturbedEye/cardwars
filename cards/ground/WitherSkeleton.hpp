#pragma once

struct engine::cards::WitherSkeleton : public virtual engine::ACard
{
	explicit WitherSkeleton(const Vec2u &window_size);
	int getDamage() const;
	int getHealth() const;
	int getCost() const;

	inline const static std::string CardName = "WitherSkeleton";
	inline const static ACard::Types CardType = Types::Ground;
private:
	int Damage; 
	int Health; 
	int Cost;
	inline const static CardTexture texture = CardTexture("images\\witherskeleton.jpg");

	virtual void movement() final override;
	virtual void onUse() final override;
};

engine::cards::WitherSkeleton::WitherSkeleton(const Vec2u &window_size)
	: ACard(window_size)
{
	Json js = load(CardType);
	Cost = js[CardName][CostStr];
	Damage = js[CardName][DamageStr];
	Health = js[CardName][HealthStr];
	Description = js[CardName][DescriptionStr];
	cover.setTexture(*texture);
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


