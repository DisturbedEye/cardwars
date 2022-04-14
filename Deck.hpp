#pragma once

class engine::Deck : public sf::Drawable
{
	void shuffle();
	ACollection collection;
	void draw(sf::RenderTarget &win, sf::RenderStates st) const override;
	inline const static int max_card_count_by_width = 3;
public:
	explicit Deck(const ACollection &cols)
	{
		collection = cols;
	}
};