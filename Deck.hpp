#pragma once
namespace rune
{
	template<const engine::ScrollType ScType>
	class Deck : public engine::Scrollable<Card, ScType>
	{
	public:
		Deck(Collection col, int card_count, const float &height);
		Deck() : collection() {}
		void shuffle() const; // shuffle deck
		private:
		Collection collection;
	};

	template<const engine::ScrollType ScType>
	Deck<ScType>::Deck(Collection col, int card_count, const float &length)
		: engine::Scrollable<Card, ScType>(&col->cards, card_count, length), collection(col)
	{
	}

	template<const engine::ScrollType ScType>
	void Deck<ScType>::shuffle() const
	{
		srand(static_cast<unsigned int>(std::time(NULL)));
		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(collection->cards.begin(), collection->cards.end(), generator);
	}
}