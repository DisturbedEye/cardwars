#pragma once

struct engine::collections::SuperCollection : public engine::ACollection
{
	inline const static std::string Name = "Collection of All";
	const std::list<ACollection::ACard *> &getCards() { return cards; }
	std::size_t size() { return cards.size(); }
	SuperCollection(const Vec2f &screen_resolution);
private:
	std::list<ACollection::ACard *> cards;
};


engine::collections::SuperCollection::SuperCollection(const Vec2f &scr)
{
	ACollection::WitherSkeleton w(scr);
	cards.push_back(&w);
}