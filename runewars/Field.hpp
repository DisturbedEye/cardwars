#pragma once

namespace rune
{
	class Field : public sf::Drawable
	{
		std::vector<Card> *cards;
	public:
		Field() : cards() {}
	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};
}