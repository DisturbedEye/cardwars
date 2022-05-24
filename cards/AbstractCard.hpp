#pragma once

struct engine::ACard : Rect
{
	enum class Types
	{ Ground, Air, Debuff, Buff, Water, Static };
	ACard(const Vec2u &window_size);
	ACard(const ACard &) = delete;
	ACard(ACard &&) = delete;
	virtual void onUse() = 0;
	virtual void movement() = 0;
	bool isChoosed() const; // event when need to see the description
	bool isTaked();
	std::string getDescription() const;
	//static std::vector<const Keywords> getKeyWords(const std::string &desc); // founds a keywords
	void onTake();
	ACard &operator=(ACard &&) = delete;
	ACard &operator=(const ACard &) = delete;
protected:
	static Json load(Types type);
	std::string Description;
	// json elements
	inline const static std::string CostStr = "Cost";
	inline const static std::string DamageStr = "Damage";
	inline const static std::string HealthStr = "Health";
	inline const static std::string FileNameStr = "FileName";
	inline const static std::string DescriptionStr = "Description";
};


inline engine::ACard::ACard(const Vec2u &window_size)
{
	setSize(Vec2f(static_cast<float>(window_size.x)/9.f, static_cast<float>(window_size.y)/4.f));
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