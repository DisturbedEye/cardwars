#pragma once
namespace rune::collections
{
	struct Super : virtual ACollection
	{
		Super(const Vec2u &scr)
		{
			using namespace cards;
			this->cards = {
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
			};
		}
		Super() = default;
	};
}
