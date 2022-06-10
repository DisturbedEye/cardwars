#pragma once
namespace rune::collections
{
	struct SuperCollection : virtual ACollection
	{ // collection of all cards
		inline const static std::string Name = "Includes all cards";
		SuperCollection(const Vec2u &screen_resolution);
	};


	inline SuperCollection::SuperCollection(const Vec2u &scr)
	{
		using namespace cards;
		cards = {
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new WitherSkeleton(scr),
			new Gladiator(scr),
			new Gladiator(scr),
			new Gladiator(scr),
			new Gladiator(scr),
			new Gladiator(scr),
			new Gladiator(scr),
			new Gladiator(scr)
		};
	}
}