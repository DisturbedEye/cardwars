#pragma once

class engine::Deck : public sf::Drawable
{
private:
	class ACollection;
	struct SuperCollection;
	void shuffle();
	ACollection *collection;
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override;
	inline const static int max_card_count_by_width = 3;
public:
	Deck(ACollection *cols)
	{
		collection = cols;
	}
};

#include "AbstractCollection.hpp"
#include "SuperCollection.hpp"