#pragma once
struct WhitherSkeleton : public virtual engine::AbstractCard
{
public:
	void init();
	virtual void use() const override;
private:
};

void WhitherSkeleton::init()
{
	sf::Texture texture;
	texture.loadFromFile("images\\witherskeleton.jpg");
	cover.setTexture(&texture);
}