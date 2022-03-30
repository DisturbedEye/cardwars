#pragma once

class engine::Deck
{
public:
	~Deck();
	void addCard(AbstractCard *card);

private:
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