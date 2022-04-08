#pragma once
class engine::ACollection 
{
protected:
	std::vector<ACard *> cards;
public:
	ACollection() { }
	~ACollection() 
	{
		for (auto &i : cards)
			delete &i;
	}
	ACollection(const std::vector<ACard *> &cardlist);
	ACollection(const ACollection &col) : cards(col.cards) {}
	const std::vector<ACard *> &getCards() const;
	std::size_t size() const { return cards.size(); }
};

engine::ACollection::ACollection(const std::vector<engine::ACard *> &cardlist)
{
	cards = cardlist;
}

inline const std::vector<engine::ACard *> &engine::ACollection::getCards() const
{
	return cards;
}



#include "AbstractCard.hpp"
#include "WitherSkeleton.hpp"