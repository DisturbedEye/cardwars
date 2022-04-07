#pragma once

struct engine::collections::SuperCollection : public virtual engine::ACollection
{
	inline const static std::string Name = "Includes all cards";
	const std::list<ACollection::ACard *> &getCards() { return cards; }
	std::size_t size() { return cards.size(); }
	SuperCollection(const Vec2f &screen_resolution);
};


engine::collections::SuperCollection::SuperCollection(const Vec2f &scr)
{
	ACollection::WitherSkeleton w(scr);
	cards.push_back(&w);
}