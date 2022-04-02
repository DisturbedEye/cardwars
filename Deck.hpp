#pragma once

class engine::Deck
{
public:
	~Deck();
	void addCard(AbstractCard *card);
	const std::list<AbstractCard *> &getCards() const;

private:
	void shuffle();
	std::list<AbstractCard *> cards;
};

engine::Deck::~Deck()
{
	for (auto i : cards)
	{
		delete i;
	}
}
void engine::Deck::addCard(AbstractCard *card)
{
	cards.push_back(card);
}