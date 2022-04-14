#pragma once
class engine::ACollection 
{
protected:
	std::vector<ACard *> cards;
public:
	ACollection(const std::vector<ACard *> &cardlist);
	ACollection(const ACollection &col);
	ACollection() {  }
	~ACollection();
	const std::vector<ACard *> &getCards() const;
	Vec2f getCardSize() const;
	const std::vector<ACard *> &operator*() { return cards; }
	ACard *operator[](const size_t &id) { return cards[id]; }
};

engine::ACollection::ACollection(const std::vector<engine::ACard *> &cardlist)
{
	cards = cardlist;
}

engine::ACollection::ACollection(const ACollection &col)
{
	cards = col.cards;
}

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