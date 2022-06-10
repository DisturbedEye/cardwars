#pragma once
namespace rune
{
	using engine::Vec2i;
	using engine::Vec2f;
	using engine::Vec2u;
	using engine::Vec2;
	using engine::Vec3;
	using engine::Vec3f;
	using engine::Vec3u;
	using engine::Vec3i;
	using engine::Json;
	using engine::Rect;
	using engine::Convex;
	using engine::Circle;

	struct ACard;
	class Player;
	class Field;
	using Card = ACard *;
	namespace cards
	{
		struct Gladiator;
		struct WitherSkeleton;
	}
	/////////////////
	// collections //
	class ACollection;
	using Collection = ACollection *;
	namespace collections
	{
		struct SuperCollection;
	}
	template<const engine::ScrollType ScType = engine::ScrollType::Vertical>
	class Deck;
}