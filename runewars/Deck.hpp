#pragma once
namespace rune
{
	template<const engine::ScrollType ScType>
	class Deck : public engine::Scrollable<Card, ScType>
	{
	public:
		Deck(Collection col, const unsigned &card_count, const float &height); // constructor
		Deck() : collection() {} // default constructor 
		void shuffle(); // shuffle deck
	private:
		Collection collection;
	};

	template<const engine::ScrollType ScType>
	Deck<ScType>::Deck(Collection collection, const unsigned &count, const float &length) // constructor
		: engine::Scrollable<Card, ScType>(collection->cards, count, length), collection(collection)
	{
		
	}

	template<const engine::ScrollType ScType>
	void Deck<ScType>::shuffle()
	{
		engine::random().shuffle(this->begin(), this->end());
	}
}