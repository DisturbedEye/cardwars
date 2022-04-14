#pragma once

struct engine::cards::Gladiator : public virtual engine::ACard
{
	explicit Gladiator(const Vec2u &window_size);
	int getDamage() const;
	int getHealth() const;
	int getCost() const;

	inline const static std::string CardName = "Gladiator";
	inline const static ACard::Types CardType = Types::Ground;
private:
	int Damage;
	int Health; 
	int Cost;
	/*
	* card texture is static becouse every 
	* of card dont need to load a new texture (static object call destructor in the end of the programm) 
	*/
	inline const static CardTexture texture = CardTexture("images\\gladiator.jpg");

	virtual void movement() final override;
	virtual void onUse() final override;
};


engine::cards::Gladiator::Gladiator(const Vec2u &window_size)
	: ACard(window_size)
{
	Json js = load(CardType);
	Cost = js[CardName][CostStr];
	Damage = js[CardName][DamageStr];
	Health = js[CardName][HealthStr];
	Description = js[CardName][DescriptionStr];
	cover.setTexture(*texture);
}
int engine::cards::Gladiator::getDamage() const
{
	return Damage;
}

int engine::cards::Gladiator::getHealth() const
{
	return Health;
}

int engine::cards::Gladiator::getCost() const
{
	return Cost;
}

void engine::cards::Gladiator::onUse()
{

}
void engine::cards::Gladiator::movement()
{

}

