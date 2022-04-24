#pragma once

struct engine::collections::SuperCollection : virtual ACollection
{ // collection of all cards
	inline const static std::string Name = "Includes all cards";
	SuperCollection(const Vec2u &screen_resolution);
};


inline engine::collections::SuperCollection::SuperCollection(const Vec2u &scr)
{
	using namespace cards;
	cards = {
		new WitherSkeleton(scr),
		new Gladiator(scr)
	};
}