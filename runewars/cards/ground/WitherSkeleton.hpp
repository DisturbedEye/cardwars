#pragma once

namespace rune::cards
{
	struct WitherSkeleton : virtual ACard
	{
		explicit WitherSkeleton(const Vec2u &window_size);
		int getDamage() const;
		int getHealth() const;
		int getCost() const;

		inline const static std::string CardName = "WitherSkeleton";
		inline const static Type CardType = Type::Ground;
	private:
		int Damage;
		int Health;
		int Cost;
		inline const static engine::CardTexture texture = engine::CardTexture("images\\witherskeleton.jpg");

		void movement() final override;
		void onUse() final override;
	};
	inline WitherSkeleton::WitherSkeleton(const Vec2u &window_size)
		: ACard(window_size, *texture)
	{
		Json js = load(CardType);
		Cost = js[CardName][CostStr];
		Damage = js[CardName][DamageStr];
		Health = js[CardName][HealthStr];
		Description = js[CardName][DescriptionStr];
	}
	inline int WitherSkeleton::getDamage() const
	{
		return Damage;
	}

	inline int WitherSkeleton::getHealth() const
	{
		return Health;
	}

	inline int WitherSkeleton::getCost() const
	{
		return Cost;
	}

	inline void WitherSkeleton::onUse()
	{

	}
	inline void WitherSkeleton::movement()
	{

	}
}
