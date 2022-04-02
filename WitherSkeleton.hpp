#pragma once

struct engine::cards::WitherSkeleton : public virtual engine::AbstractCard
{
	const inline static int Damage = 2; // temporary
	const inline static int Health = 4; // temporary
	const inline static int Cost = 3;
	const inline static sf::String Name = "Wither Skeleton";
	const inline static sf::String Description = "Something";
	const inline static sf::String Type = "This Type";
	explicit WitherSkeleton(const Vec2f &window_size);
	virtual void onUse() const override;
};

engine::cards::WitherSkeleton::WitherSkeleton(const Vec2f &window_size)
{
	sf::Texture texture;
	texture.loadFromFile("images\\witherskeleton.jpg");
	cover.setTexture(&texture);
}


void engine::cards::WitherSkeleton::onUse() const
{
	
}


