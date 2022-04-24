#pragma once
class engine::ACollection : public sf::Drawable
{
public:
	ACollection(const std::vector<ACard*> &card_list);
	ACollection(const ACollection &col);
	ACollection() {}
	virtual ~ACollection();
	Vec2f getCardSize() const;
	size_t size() const { return cards.size(); }
	void setCardPosition(const size_t &id, const Vec2f &pos) { cards[id]->setPosition(pos); }
	ACard &operator[](const size_t &id) { return *cards[id]; }
	const ACard &operator[](const size_t &id) const { return *cards[id]; }
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

inline sf::Vector2f engine::ACollection::getCardSize() const 
{
	return cards[0]->getSize();
}

inline void engine::ACollection::draw(sf::RenderTarget &win, sf::RenderStates st) const
{
	for (auto &card : cards)
		win.draw(*card);
}
