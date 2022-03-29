#pragma once

class engine::Deck
{
public:
	~Deck();
	void addCard(const AbstractCard &card);

private:
	std::list<AbstractCard *> cards;
};