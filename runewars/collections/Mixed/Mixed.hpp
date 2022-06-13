#pragma once


namespace rune::collections
{
	struct Mixed : virtual ACollection
	{
		Mixed(const ACollection &col1, const ACollection &col2) : ACollection(col1.cards + col2.cards) {}
		Mixed() = default;
	};
}
