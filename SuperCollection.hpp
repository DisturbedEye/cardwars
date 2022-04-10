#pragma once

struct engine::collections::SuperCollection : public virtual engine::ACollection
{
	inline const static std::string Name = "Includes all cards";
	SuperCollection(const Vec2u &screen_resolution);
};


engine::collections::SuperCollection::SuperCollection(const Vec2u &scr)
{
	cards::WitherSkeleton w(scr);
	cards.push_back(&w);
}