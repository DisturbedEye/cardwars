class engine::CardSorter
{
	CardSorter();
	~CardSorter();
	void sortInSegment(const Vec2f p1, const Vec2f p2);
	void addCard(const AbstractCard *card);
private:
	std::list<AbstractCard *> cards;
	void sort();
};


engine::CardSorter::~CardSorter()
{
	for (auto i : cards)
		delete i;
}