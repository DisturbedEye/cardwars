#pragma once

struct engine::cards::WitherSkeleton : virtual ACard
{
	explicit WitherSkeleton(const Vec2u &window_size);
	int getDamage() const;
	int getHealth() const;
	int getCost() const;

	inline const static std::string CardName = "WitherSkeleton";
	inline const static Types CardType = Types::Ground;
private:
	int Damage; 
	int Health; 
	int Cost;
	inline const static CardTexture texture = CardTexture("images\\witherskeleton.jpg");

	void movement() final override;
	void onUse() final override;
};

inline engine::cards::WitherSkeleton::WitherSkeleton(const Vec2u &window_size)
	: ACard(window_size)
{
	Json js = load(CardType);
	Cost = js[CardName][CostStr];
	Damage = js[CardName][DamageStr];
	Health = js[CardName][HealthStr];
	Description = js[CardName][DescriptionStr];
	cover.setTexture(*texture);
}

inline int engine::cards::WitherSkeleton::getDamage() const
{
	return Damage;
}

inline int engine::cards::WitherSkeleton::getHealth() const
{
	return Health;
}

inline int engine::cards::WitherSkeleton::getCost() const
{
	return Cost;
}

inline void engine::cards::WitherSkeleton::onUse()
{
	
}
inline void engine::cards::WitherSkeleton::movement()
{

}


