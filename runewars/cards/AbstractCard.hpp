#pragma once

namespace rune
{
	struct ACard : sf::Drawable, sf::Transformable, ngn::ClickableRect
	{
		enum class Type
		{ Ground, Air, Debuff, Buff, Water, Static };
		ACard(const Vec2u &window_size, const sf::Texture &t);
		ACard(const ACard &) = delete;
		ACard(ACard &&) = delete;
		virtual void onUse() = 0;
		virtual void movement() = 0;
		bool isChoosed() const; // event when need to see the description
		bool isTaked();
		Vec2f getSize() const { return cover.getSize(); }
		std::string getDescription() const;
		//static std::vector<const Keywords> getKeyWords(const std::string &desc); // founds a keywords
		void onTake();
		ACard &operator=(ACard &&) = delete;
		ACard &operator=(const ACard &) = delete;
	protected:
		static Json load(Type type);
		inline static std::string Description;
		// json elements

		inline const static std::string CostStr = "Cost";
		inline const static std::string DamageStr = "Damage";
		inline const static std::string HealthStr = "Health";
		inline const static std::string FileNameStr = "FileName";
		inline const static std::string DescriptionStr = "Description";
	private:
		Rect cover;
		void draw(sf::RenderTarget &win, sf::RenderStates states) const final
		{
			states.transform *= getTransform();
			win.draw(cover, states);
		}
	};


	inline ACard::ACard(const Vec2u &window_size, const sf::Texture &t)
	{
		cover.setSize(Vec2f(static_cast<float>(window_size.x)/9.f, static_cast<float>(window_size.y)/4.f));
		cover.setTexture(&t);
	}

	inline Json ACard::load(const Type type)
	{
		std::string filename = "Ground"; // default
		switch (type)
		{
		case Type::Debuff:
			filename = "Debuff";
			break;
		case Type::Air:
			filename = "Air";
			break;
		case Type::Buff:
			filename = "Buff";
			break;
		case Type::Static:
			filename = "Static";
			break;
		case Type::Water:
			filename = "Water";
			break;
		}
		engine::JsonFile jsf("src/cards", filename);
		return jsf.load();
	}



	inline bool ACard::isChoosed() const
	{
		return false;
	}
	inline bool ACard::isTaked()
	{
		return false;
	}
	inline void ACard::onTake()
	{

	}
}