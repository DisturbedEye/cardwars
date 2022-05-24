#pragma once

template<const engine::ScrollType ScType = engine::ScrollType::Vertical>
class engine::Deck : public Scrollable<Card, ScType>
{
public:
	Deck(Collection col, int card_count, const float &height);
	void shuffle() const; // shuffle deck
private:
	Collection collection;
};

template<const engine::ScrollType ScType>
engine::Deck<ScType>::Deck(Collection col, int card_count, const float &length)
	: Scrollable<Card, ScType>(&col->cards, card_count, length), collection(col)
{
	this->setSize(card_count, length);
}

template<const engine::ScrollType ScType>
void engine::Deck<ScType>::shuffle() const
{
	srand(static_cast<unsigned int>(std::time(NULL)));
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(collection->cards.begin(), collection->cards.end(), generator);
}