#pragma once
class engine::Deck::ACollection 
{
protected:
	struct ACard;
	struct WitherSkeleton;
	std::list<ACard *> cards;
public:
	ACollection() { }
	~ACollection() 
	{
		for (auto &i : cards)
			delete &i;
	}
	ACollection(const std::list<ACard *> &cardlist);
	ACollection(const ACollection &col) : cards(col.cards) {}
	const std::list<ACard *> &getCards() const;
	std::size_t size() const { return cards.size(); }
	ACollection &operator=(const ACollection &collection);
	ACollection &operator=(const ACollection *collection);
};

engine::Deck::ACollection::ACollection(const std::list<ACard *> &cardlist)
{
	cards = cardlist;
}

inline const std::list<engine::Deck::ACollection::ACard *> &engine::Deck::ACollection::getCards() const
{
	return cards;
}

engine::Deck::ACollection &engine::Deck::ACollection::operator=(const engine::Deck::ACollection &collection)
{
	this->cards = collection.cards;
}

engine::Deck::ACollection &engine::Deck::ACollection::operator=(const engine::Deck::ACollection *collection)
{
	this->cards = collection->cards;
}


#include "AbstractCard.hpp"
#include "WitherSkeleton.hpp"