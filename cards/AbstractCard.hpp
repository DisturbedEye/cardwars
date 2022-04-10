#pragma once

struct engine::ACard : public sf::Drawable
{
	enum class Types
	{ Ground, Air, Debuff, Buff, Water, Static };

	enum class Keywords
	{
	};
	ACard(const Vec2u &window_size);
	virtual void onUse() = 0;
	void setPosition(const Vec2f &p);
	void setOrigin(const Vec2f &o);
	void setSize(const Vec2f &s);
	virtual void movement() = 0;
	~ACard() 
	{
		delete texture;
	}
	Vec2f getPosition() const;
	Vec2f getOrigin() const;
	Vec2f getSize() const;
	bool isChoosed() const; // event when need to see the description
	bool isTaked();
	std::string getDescription() const;
	void onTake();
protected:
	Rect cover = Rect();
	static Json load(const Types type);
	sf::Texture *texture = new sf::Texture();
	static std::vector<Keywords> getKeyWords(const std::string &desc);
	std::string Description;
	// json elements
	inline const static std::string CostStr = "Cost";
	inline const static std::string DamageStr = "Damage";
	inline const static std::string HealthStr = "Health";
	inline const static std::string DescriptionStr = "Desctiption";

private:
	void draw(sf::RenderTarget &window, sf::RenderStates states) const final override;
};


engine::ACard::ACard(const Vec2u &window_size)
{
	cover.setSize((Vec2f(static_cast<float>(window_size.x)/9.f, static_cast<float>(window_size.y)/4.f)));
}

nlohmann::json engine::ACard::load(const Types type)
{
	std::string filename = "Ground";
	switch (type)
	{
	case Types::Debuff:
		filename = "Debuff";
		break;
	case Types::Ground:
		filename = "Ground";
		break;
	case Types::Air:
		filename = "Air";
		break;
	case Types::Buff:
		filename = "Buff";
		break;
	case Types::Static:
		filename = "Static";
		break;
	case Types::Water:
		filename = "Water";
		break;
	}
	JsonFile jsf("src/cards", filename);
	return jsf.load();
}


bool engine::ACard::isChoosed() const
{
	return false;
}
bool engine::ACard::isTaked()
{
	return false;
}
void engine::ACard::onTake()
{

}
void engine::ACard::setPosition(const Vec2f &p)
{
	cover.setPosition(p);
}
void engine::ACard::setOrigin(const Vec2f &origin)
{
	cover.setOrigin(origin);
}
void engine::ACard::setSize(const Vec2f &s)
{
	cover.setSize(s);
}
inline std::string engine::ACard::getDescription() const
{
	return Description;
}
inline sf::Vector2f engine::ACard::getPosition() const
{
	return cover.getPosition();
}
inline sf::Vector2f engine::ACard::getSize() const
{
	return cover.getSize();
}
inline sf::Vector2f engine::ACard::getOrigin() const
{
	return cover.getOrigin();
}
void engine::ACard::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(cover);
}