#pragma once
class engine::ACollection 
{
protected:
	// cards //

	struct ACard;
	struct WitherSkeleton;

	///////////
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
};

engine::ACollection::ACollection(const std::list<ACard *> &cardlist)
{
	cards = cardlist;
}

inline const std::list<engine::ACollection::ACard *> &engine::ACollection::getCards() const
{
	return cards;
}



#include "AbstractCard.hpp"
#include "WitherSkeleton.hpp"