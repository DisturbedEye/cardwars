#include "runewars/RuneWars.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &v)
{
	out << "{ " << v.x << ", " << v.y << " }";
	return out;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const sf::Rect<T> &rect)
{
	out << "{ " << sf::Vector2<T>(rect.left, rect.top) << ", " << sf::Vector2<T>(rect.width, rect.height) << " }";
	return out;
}

namespace parametrs
{
	static sf::Vector2u resolution = engine::getInfoResolution();
	static bool vsync = engine::getInfoVsync();
	static unsigned int frame_limit = engine::getInfoFramerateLimit();
	static int window_mode = engine::getInfoVideoMode();
	static sf::Music soundtrack;
	static float default_volume = 10.f;
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
	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y, mode.bitsPerPixel), "Rune Wars", window_mode);
	window.setFramerateLimit(frame_limit);
	window.setVerticalSyncEnabled(vsync);
	soundtrack.openFromFile("audio\\garazh_phonk.wav");
	soundtrack.play();
	soundtrack.setLoop(true);
	soundtrack.setVolume(default_volume);
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
	using namespace parametrs;
	using emath::pi;
	const Vec2u ures = window.getSize();
	const Vec2f res = Vec2f(ures);
	sf::Mouse m;
	Vec2f mpos = Vec2f(m.getPosition(window));
	auto &font = loadFont();
	rcolls::Super all_cards(ures);
	auto deck = rune::Deck(&all_cards, 3u, res.y/3.f);
	const float &whl_speed = 10;
	Button shuffle(Vec2f{300, 75}, "shuffle", font);
	shuffle.setPosition(2.f*res.x/3.f - shuffle.getSize().x, res.y / 2.f);
	sf::Color shf_color = sf::Color(120, 240, 100);
	shuffle.setFillColor(shf_color);
	while (window.isOpen())
	{
		float d1 = 0;
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseWheelMoved:
				d1 = clamp(static_cast<float>(event.mouseWheel.delta), -1, 1);
			}
		}
		mpos = Vec2f(m.getPosition(window));
		window.clear();
		deck.setSliderPos(deck.getSlider().getPosition().y - d1*whl_speed);
		if (shuffle.isIntersected(mpos))
			shuffle.setFillColor(mix(shf_color, sf::Color::White));
		else
			shuffle.setFillColor(shf_color);
		if (shuffle.isPressed(sf::Mouse::Button::Left, mpos))
			deck.shuffle();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			return;
		window.draw(shuffle);
		window.draw(deck);
		window.display();
	}
}
