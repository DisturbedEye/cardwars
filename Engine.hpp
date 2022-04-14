#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <typeinfo>
#include <algorithm>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include <exception>

namespace engine
{
	using namespace std::string_literals;
	typedef sf::Vector2f Vec2f;
	typedef sf::Vector2i Vec2i;
	typedef sf::Vector2u Vec2u;
	typedef sf::RectangleShape Rect;
	typedef sf::CircleShape Circle;
	using Json = nlohmann::json;
	typedef sf::ConvexShape Convex; // выпуклый многоугольник
	
	std::vector<int> video_modes = { sf::Style::Close, sf::Style::None, sf::Style::Fullscreen };
	std::map<int, int> reverse_modes = { {video_modes[0], 0}, {video_modes[1], 1}, {video_modes[2], 2} };
	
	class JsonFile;

	size_t getVideoModesCount() { return video_modes.size(); }
	void create_infof();
	Json load_infof();
	void resetInfoResolution(const unsigned int x, const unsigned int y);
	void resetInfoFramerateLimit(const unsigned int lim);
	void resetInfoVsync(const bool b);
	void resetInfoVideoMode(const int mode);
	int getInfoVideoMode();
	Vec2u getInfoResolution();
	unsigned int getInfoFramerateLimit();
	bool getInfoVsync();
	sf::Texture &loadCardTexture(const std::string &path); // path - path/file.type 


	struct Button;
	class CardTexture;
	class Deck;
	//    cards    //

	struct ACard;
	namespace cards
	{
		struct Gladiator;
		struct WitherSkeleton;
	}

	/////////////////
	// collections //

	class ACollection;
	namespace collections
	{
		struct SuperCollection;
	}

	/////////////////
	namespace math
	{
		const float pi = 3.14159265f;
		const float rad = pi / 180;
		bool inside(const Vec2f &point, const Rect &rect);
		bool inside(const Vec2f &point, const Vec2f ro, const Vec2f rs);
		float length(const Vec2f &v);
		bool around(const float &x, const int n);
		bool belongs(const float &x, const float &m, const float &n);
		bool inside(const Vec2f &point, const Convex &polygon);
		bool inside(const Vec2f &point, const Circle &circle);
		sf::Color mix(const sf::Color &c1, const sf::Color &c2);
		template <class T>
		size_t get_index(const std::vector<T> &v, const T n);
		template <class T>
		bool inside(const std::vector<T> &v, const T n);
	}
}

#include "FileManagement.hpp"

#include "emath.hpp"
#include "button.hpp"
#include "CardTexture.hpp"
// cards //

#include "cards/AbstractCard.hpp"
#include "cards/ground/WitherSkeleton.hpp"
#include "cards/ground/Gladiator.hpp"
// collections //

#include "AbstractCollection.hpp"

#include "SuperCollection.hpp"

/////////////////
#include "Deck.hpp"