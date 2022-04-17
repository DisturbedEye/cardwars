#pragma once

struct engine::cards::Gladiator : public virtual ACard
{
	explicit Gladiator(const Vec2u &window_size);
	int getDamage() const;
	int getHealth() const;
	int getCost() const;

	inline const static std::string CardName = "Gladiator";
	inline const static Types CardType = Types::Ground;
private:
	int Damage;
	int Health; 
	int Cost;
	inline const static CardTexture texture = CardTexture("images\\gladiator.jpg");

	void movement() final;
	void onUse() final;
};


inline engine::cards::Gladiator::Gladiator(const Vec2u &window_size)
	: ACard(window_size)
{
	Json js = load(CardType);
	Cost = js[CardName][CostStr];
	Damage = js[CardName][DamageStr];
	Health = js[CardName][HealthStr];
	Description = js[CardName][DescriptionStr];
	cover.setTexture(*texture);
}
inline int engine::cards::Gladiator::getDamage() const
{
	return Damage;
}

inline int engine::cards::Gladiator::getHealth() const
{
	return Health;
}

inline int engine::cards::Gladiator::getCost() const
{
	return Cost;
}

inline void engine::cards::Gladiator::onUse()
{

}
inline void engine::cards::Gladiator::movement()
{

}

