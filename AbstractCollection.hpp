#pragma once
class engine::ACollection : public sf::Drawable
{
public:
	ACollection(const std::vector<ACard*> &card_list);
	ACollection(const ACollection &col);
	ACollection() {}
	~ACollection();
	const std::vector<ACard *> &getCards() const;
	Vec2f getCardSize() const;
	size_t getCardCount() const { return cards.size(); }
	const std::vector<ACard *> &operator*() { return cards; }
	ACard *operator[](const size_t &id) { return cards[id]; }
protected:
	std::vector<ACard *> cards;
private:
	void draw(sf::RenderTarget &win, sf::RenderStates st) const;
	friend class Deck;
};

inline engine::ACollection::ACollection(const std::vector<ACard*> &card_list) : cards(card_list) {}

inline engine::ACollection::ACollection(const ACollection &col) : cards(col.cards) {}

inline engine::ACollection::~ACollection()
{
	for (auto &card : cards)
		delete card;
}

inline const std::vector<engine::ACard *> &engine::ACollection::getCards() const
{
	return cards;
}

inline sf::Vector2f engine::ACollection::getCardSize() const 
{
	return cards[0]->getSize();
}

inline void engine::ACollection::draw(sf::RenderTarget &win, sf::RenderStates st) const
{
	for (auto &card : cards)
		win.draw(*card);
}
