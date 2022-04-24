#pragma once

struct engine::ACard : sf::Drawable
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
	void setPosition(const float &x, const float &y);
	void setOrigin(const float &x, const float &y);
	void setSize(const float &x, const float &y);
	virtual void movement() = 0;
	Vec2f getPosition() const;
	Vec2f getOrigin() const;
	Vec2f getSize() const;
	bool isChoosed() const; // event when need to see the description
	bool isTaked();
	std::string getDescription() const;
	static std::vector<const Keywords> getKeyWords(const std::string &desc);
	sf::FloatRect getGlobalBounds() const { return cover.getGlobalBounds(); }
	sf::FloatRect getLocalBounds() const { return cover.getLocalBounds(); }
	void onTake();
protected:
	Rect cover = Rect();
	static Json load(Types type);
	std::string Description;
	// json elements
	inline const static std::string CostStr = "Cost";
	inline const static std::string DamageStr = "Damage";
	inline const static std::string HealthStr = "Health";
	inline const static std::string FileNameStr = "FileName";
	inline const static std::string DescriptionStr = "Description";

private:
	void draw(sf::RenderTarget &window, sf::RenderStates states) const final override;
};


inline engine::ACard::ACard(const Vec2u &window_size)
{
	cover.setSize((Vec2f(static_cast<float>(window_size.x)/9.f, static_cast<float>(window_size.y)/4.f)));
}

inline nlohmann::json engine::ACard::load(const Types type)
{
	std::string filename = "Ground"; // default
	switch (type)
	{
	case Types::Debuff:
		filename = "Debuff";
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



inline bool engine::ACard::isChoosed() const
{
	return false;
}
inline bool engine::ACard::isTaked()
{
	return false;
}
inline void engine::ACard::onTake()
{

}
inline void engine::ACard::setPosition(const Vec2f &p)
{
	cover.setPosition(p);
}
inline void engine::ACard::setOrigin(const Vec2f &origin)
{
	cover.setOrigin(origin);
}
inline void engine::ACard::setSize(const Vec2f &s)
{
	cover.setSize(s);
}
inline void engine::ACard::setPosition(const float &x, const float &y)
{
	cover.setPosition(x, y);
}
inline void engine::ACard::setOrigin(const float &x, const float &y)
{
	cover.setOrigin(x, y);
}
inline void engine::ACard::setSize(const float &x, const float &y)
{
	cover.setSize(Vec2f(x, y));
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
inline void engine::ACard::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(cover);
}