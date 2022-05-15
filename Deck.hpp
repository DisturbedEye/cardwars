#pragma once

template<engine::ScrollType T = engine::ScrollType::Vertical>
class engine::Deck : public Scrollable<Card, T>
{
public:
	Deck(Collection col, int card_count, const float &height);
	void shuffle() const; // shuffle deck
private:
	Collection collection;
};

template<engine::ScrollType T>
engine::Deck<T>::Deck(Collection col, int card_count, const float &length)
	: Scrollable<Card, T>(&col->cards, card_count, length), collection(col)
{
	this->setSize(card_count, length);
}

template<engine::ScrollType T> 
void engine::Deck<T>::shuffle() const
{
	srand(static_cast<unsigned int>(std::time(NULL)));
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(collection->cards.begin(), collection->cards.end(), generator);
}