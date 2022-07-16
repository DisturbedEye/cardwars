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
	class AAction;
	namespace actions
	{
		
	}
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
	namespace fonts
	{
		inline sf::Font loadFont(const std::string &font_file_path)
		{
			using namespace std::string_literals;
			sf::Font font;
			if (!font.loadFromFile(font_file_path))
			{
				std::cout << "FileNotFoundError: '"s + font_file_path + "' path or file type is not correct";
				throw;
			}
			return font;
		}
		const static sf::Font RZSerif = loadFont("Fonts/RezaZulmiSerif/RezaZulmiSerif.ttf");
		const static sf::Font IgraSans = loadFont("Fonts/IgraSans/IgraSans.otf");
		const static sf::Font Winston = loadFont("Fonts/Winston/Winston-Regular.ttf");
	}
	static sf::Music music_channel;
	namespace menu
	{
		class Settings;
		void about_us(sf::RenderWindow &);
		int main(sf::RenderWindow &);
		void settings(sf::RenderWindow &);
		void start(sf::RenderWindow &);
	}
}
namespace rcolls = rune::collections;
namespace rcards = rune::cards;

// including headers//
//		actions		//

#include "actions/AbstractAction.hpp"

//		cards		//

#include "cards/AbstractCard.hpp"

#include "cards/ground/Gladiator.hpp"
#include "cards/ground/WitherSkeleton.hpp"

//	  collections   //

#include "collections/AbstractCollection.hpp"

#include "collections/Mixed/Mixed.hpp"
#include "collections/Super/Super.hpp"

//		other		//

#include "Deck.hpp"
#include "Field.hpp"
#include "Player.hpp"


//		menu	    //

#include "menu/SettingsFile.hpp"

#include "menu/main.hpp"
#include "menu/settings.hpp"
#include "menu/about_us.hpp"
#include "menu/start.hpp"
//////////////////////
