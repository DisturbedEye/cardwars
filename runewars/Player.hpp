#pragma once


namespace rune
{
	class Player
	{
		Deck<> deck;
		Field play_field;
		static std::string name;

	public:
		Player(Deck<> d) : deck(d) {}
		Player() = default;
	};
}