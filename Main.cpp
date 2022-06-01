#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include <SFML/Audio.hpp>

template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &v)
{
	out << "{ " << v.x << ", " << v.y << " }";
	return out;
}

namespace parametrs
{
	sf::Vector2u default_resolution = engine::getInfoResolution();
	bool vsync = engine::getInfoVsync();
	unsigned int frame_limit = engine::getInfoFramerateLimit();
	int window_mode = engine::getInfoVideoMode();
}
sf::Font &loadFont()
{
	static sf::Font font;
	if (!font.loadFromFile("Fonts\\RezaZulmiSerif\\RezaZulmiSerif.ttf"))
	{
		std::cout << "FileNotFoundError: File \"RezaZulmiSerif.ttf\" not found!";
		throw;
	}
	return font;
}
namespace menu
{
	void about_us(sf::RenderWindow &);
	int main(sf::RenderWindow &);
	void settings(sf::RenderWindow &);
	void start(sf::RenderWindow &);
}

#include "menu/main.hpp"
#include "menu/settings.hpp"
#include "menu/about_us.hpp"

int main()
{
	using namespace parametrs;
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(default_resolution.x, default_resolution.y, mode.bitsPerPixel), "Rune Wars", window_mode);
	window.setFramerateLimit(frame_limit);
	window.setVerticalSyncEnabled(vsync);
	sf::Music ms;
	ms.openFromFile("audio\\garazh_phonk.ogg");
	ms.play();
	ms.setLoop(true);
	ms.setVolume(10.f);
	int position = 0; // 0 - main menu, 1 - start game, 2 - settings, 3 about us, 4 - exit
	while (position != 4)
	{
		position = menu::main(window);
		if (position == 1) // start game
			menu::start(window);
		else if (position == 2) // settings
			menu::settings(window);
		else if (position == 3) // about us
			menu::about_us(window);
	}
	return 0;
}

inline void menu::start(sf::RenderWindow &window)
{
	using engine::Button;
	using emath::clamp;
	using engine::Vec2f;
	using engine::Vec2u;
	using emath::mix;
	using engine::Rect;
	using namespace engine::cards;
	using namespace parametrs;
	using emath::pi;
	const Vec2u ures = window.getSize();
	const Vec2f res = Vec2f(ures);
	sf::Mouse m;
	Vec2f mpos = Vec2f(m.getPosition(window));
	auto &font = loadFont();
	Button button(Vec2f(300, 60), "Some text", font, 24);
	const sf::Color bcolor = sf::Color(230, 100, 100);
	button.setColor(sf::Color(230, 100, 100));
	ecolls::SuperCollection sup(window.getSize());
	engine::Deck deck(&sup, 2u, res.y/2);
	deck.setPosition(res.x/5, res.y/4);
	Rect rect(Vec2f(deck.getSize().x + deck.getSliderSize().x, deck.getSize().y));
	rect.setFillColor(sf::Color(50, 50, 50));
	float sens = 25; // slider speed
	float senst = 0;
	bool a = false;
	rect.setPosition(deck.getPosition());
	Vec2u u_decksize = Vec2u(static_cast<unsigned>(deck.getGlobalBounds().width + deck.getSliderSize().x), static_cast<unsigned>(deck.getGlobalBounds().height));
	Button shuffleb(Vec2f(300, 60), "Shuffle", font, 36);
	shuffleb.setPosition(res.x/36, res.y/2);
	engine::Cutter cut(u_decksize, &deck);
	while (window.isOpen())
	{
		float d1 = 0;
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseWheelMoved:
				d1 = clamp(static_cast<float>(event.mouseWheel.delta), -1, 1); // slider move coefficient
			}
		mpos = Vec2f(m.getPosition(window));
		window.clear();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;
		senst = d1 != 0.f ?  senst + sens / 4 : 0;
		deck.setSliderPos(deck.getSliderPos().y - senst * d1); // slider moving
		if (deck.sliderIsClicked(sf::Mouse::Button::Left, mpos))
			a = true;
		else if (!deck.sliderIsHold(sf::Mouse::Button::Left))
			a = false;
		if (a)
			deck.setSliderPos(mpos.y - deck.getSliderSize().y / 2);
		if (shuffleb.isIntersected(mpos))
			shuffleb.setColor(mix(bcolor, sf::Color::White));
		else shuffleb.setColor(bcolor);
		if (shuffleb.isPressed(sf::Mouse::Button::Left, mpos))
			deck.shuffle();
		window.draw(rect);
		cut.update(window);
		window.draw(cut); // we need to cut this
		window.draw(shuffleb);
		window.display();
	}
}
