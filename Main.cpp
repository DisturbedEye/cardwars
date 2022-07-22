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

int main()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	using rune::menu::Settings;
	auto settings = new Settings();
	sf::RenderWindow window(sf::VideoMode(settings->getResolution().x, settings->getResolution().y, mode.bitsPerPixel), "Rune Wars", settings->getWindowMode());
	//window.setKeyRepeatEnabled(false); // it important for keyboard and mouse button Pressing events
	window.setFramerateLimit(settings->getFramerateLimit());
	window.setVerticalSyncEnabled(settings->getVsync());
	rune::music_channel.openFromFile("audio/garazh_phonk.wav");
	rune::music_channel.play();
	rune::music_channel.setLoop(true);
	rune::music_channel.setVolume(settings->getMusicVolume());
	delete settings;
	auto position = rune::menu::Hierarchy::MainMenu;
	while (position != rune::menu::Hierarchy::Exit)
	{
		position = rune::menu::main(window);
		if (position == rune::menu::Hierarchy::StartGame) 
			rune::menu::start(window);
		else if (position == rune::menu::Hierarchy::Settings)
			rune::menu::settings(window);
		else if (position == rune::menu::Hierarchy::AboutUs)
			rune::menu::about_us(window);
	}
	return 0;
}