#pragma once
#include "../engine/Engine.hpp"

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
		struct Mixed;
		struct Super;
	}
	template<const engine::ScrollType ScType = engine::ScrollType::Vertical>
	class Deck;
}
namespace rcolls = rune::collections;
namespace rcards = rune::cards;

//    cards    //

#include "cards/AbstractCard.hpp"

#include "cards/ground/Gladiator.hpp"
#include "cards/ground/WitherSkeleton.hpp"

// collections //

#include "collections/AbstractCollection.hpp"

#include "collections/Mixed/Mixed.hpp"
#include "collections/Super/Super.hpp"

/////////////////
#include "Deck.hpp"
#include "Field.hpp"
#include "Player.hpp"