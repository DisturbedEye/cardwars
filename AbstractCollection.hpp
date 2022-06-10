#pragma once

namespace rune
{
	class ACollection : public sf::Drawable
	{
	public:
		ACollection(std::vector<ACard*> &&card_list) : cards(std::move(card_list)) {}
		ACollection(const ACollection &col) = delete;
		ACollection(ACollection &&) = delete;
		ACollection() = default;
		~ACollection() override = 0;
		Vec2f getCardSize() const;
		size_t size() const { return cards.size(); }
	
		void setCardPosition(const size_t &id, const Vec2f &pos) { cards[id]->setPosition(pos); }
		ACard &operator[](const size_t &id) { return *cards[id]; }
		const ACard &operator[](const size_t &id) const { return *cards[id]; }
		ACollection &operator=(ACollection &&) = delete;
		ACollection &operator=(const ACollection &) = delete;
	protected:
		std::vector<Card> cards;
	private:
		void draw(sf::RenderTarget &win, sf::RenderStates st) const override;
		friend class Deck<engine::ScrollType::Horizontal>;
		friend class Deck<engine::ScrollType::Vertical>;
	};

	inline ACollection::~ACollection()
	{
		for (const auto card : cards)
			delete card;
	}

	inline sf::Vector2f ACollection::getCardSize() const 
	{
		if(!cards.empty())
			return cards.front()->getSize();
		return Vec2f();
	}

	inline void ACollection::draw(sf::RenderTarget &win, sf::RenderStates st) const
	{
		for (auto card : cards)
			win.draw(*card, st);
	}
}
