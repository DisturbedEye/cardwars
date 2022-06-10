#pragma once
namespace rune::cards
{
	struct Gladiator : virtual ACard
	{
		explicit Gladiator(const Vec2u &window_size);
		int getDamage() const;
		int getHealth() const;
		int getCost() const;

		inline const static std::string CardName = "Gladiator";
		inline const static Type CardType = Type::Ground;
	private:
		int Damage;
		int Health; 
		int Cost;
		inline const static engine::CardTexture texture = engine::CardTexture("images\\gladiator.jpg");

		void movement() final override;
		void onUse() final override;
	};


	inline Gladiator::Gladiator(const Vec2u &window_size)
		: ACard(window_size, *texture)
	{
		Json js = load(CardType);
		Cost = js[CardName][CostStr];
		Damage = js[CardName][DamageStr];
		Health = js[CardName][HealthStr];
		Description = js[CardName][DescriptionStr];
	}
	inline int Gladiator::getDamage() const
	{
		return Damage;
	}

	inline int Gladiator::getHealth() const
	{
		return Health;
	}

	inline int Gladiator::getCost() const
	{
		return Cost;
	}

	inline void Gladiator::onUse()
	{

	}
	inline void Gladiator::movement()
	{

	}
}
