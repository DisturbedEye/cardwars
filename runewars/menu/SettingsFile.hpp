#pragma once

namespace rune::menu
{
	class Settings
	{
		bool vsync; // vertical synchronization
		Vec2u resolution; // resolution
		int window_mode; // window mode (sf::Style)
		unsigned frame_limit; // frame limit
		float volume; // music volume
		engine::JsonFile json = engine::JsonFile("src", "settings");

	public:
		Settings();

		void resetToDefault();

		Vec2u getResolution() { return resolution; }
		int getWindowMode() { return window_mode; }
		unsigned getFramerateLimit() { return frame_limit; }
		float getMusicVolume() { return volume; }
		bool getVsync() { return vsync; }

		void setResolution(Vec2u);
		void setWindowMode(int);
		void setFramerateLimit(unsigned);
		void setMusicVolume(float);
		void setVsync(bool);


		static Vec2u getResolution(Settings settings) { return settings.resolution; }
		static int getWindowMode(Settings settings) { return settings.window_mode; }
		static unsigned getFramerateLimit(Settings settings) { return settings.frame_limit; }
		static float getMusicVolume(Settings settings) { return settings.volume; }
		static bool getVsync(Settings settings) { return settings.vsync; }
		static void setResolution(Settings, Vec2u);
		static void setWindowMode(Settings, int);
		static void setFramerateLimit(Settings, unsigned);
		static void setMusicVolume(Settings, float);
		static void setVsync(Settings, bool);

		enum Parameters
		{
			MusicVolume, WindowMode, FramerateLimit, Resolution, Vsync
		};

	private:
		static std::map<Parameters, std::string> get_params()
		{
			return {
				{MusicVolume, "Music-Volume"},
				{WindowMode, "Window-Mode"},
				{FramerateLimit, "Framerate-Limit"},
				{Resolution, "Resolution"},
				{Vsync, "Vsync"}
			};
		}

		static std::string nameof(Parameters param) 
		{
			auto params = get_params();
			return params.at(param);
		}
		static engine::JsonFile create_default_settings();
		inline const static engine::JsonFile default_settings = engine::JsonFile(create_default_settings());
	};
	
	inline void Settings::setResolution(Settings settings, Vec2u resolution)
	{
		settings.setResolution(resolution);
	}
	inline void Settings::setFramerateLimit(Settings settings, unsigned limit)
	{
		settings.setFramerateLimit(limit);
	}
	inline void Settings::setMusicVolume(Settings settings, float volume)
	{
		settings.setMusicVolume(volume);
	}
	inline void Settings::setVsync(Settings settings, bool value)
	{
		settings.setVsync(value);
	}

	inline void Settings::setWindowMode(Settings settings, int mode)
	{
		settings.setWindowMode(mode);
	}

	inline void Settings::setResolution(Vec2u _resolution)
	{
		resolution = _resolution;
		json.js[nameof(Resolution)] = { resolution.x, resolution.y };
		json.save();
	}

	inline void Settings::setWindowMode(int _window_mode)
	{
		window_mode = _window_mode;
		json.js[nameof(WindowMode)] = window_mode;
		json.save();
	}

	inline void Settings::setFramerateLimit(unsigned framerate_limit)
	{
		frame_limit = framerate_limit;
		json.js[nameof(FramerateLimit)] = frame_limit;
		json.save();
	}

	inline void Settings::setMusicVolume(float _volume)
	{
		volume = _volume;
		json.js[nameof(MusicVolume)] = volume;
		json.save();
	}

	inline void Settings::setVsync(bool _vsync)
	{
		vsync = _vsync;
		json.js[nameof(Vsync)] = vsync;
		json.save();
	}

	inline engine::JsonFile Settings::create_default_settings()
	{
		engine::JsonFile djs("src", "default_settings");
		djs.js[nameof(Resolution)] = {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)}; // resolution
		djs.js[nameof(Vsync)] = true; // vsync
		djs.js[nameof(MusicVolume)] = 10.f; // music
		djs.js[nameof(FramerateLimit)] = 60; // frame limit
		djs.js[nameof(WindowMode)] = 4; // window mode (sf::Style::Close)
		djs.save();
		return djs;
	}

	inline Settings::Settings()
	{
		std::vector<std::string> params_name;
		for (auto &p : get_params())
			params_name.push_back(p.second);
		for (auto &name : params_name)
		{
			try
			{
				json.js.at(name);
			}
			catch (Json::out_of_range &err)
			{
				if (err.id == 403)
				{
					engine::JsonFile default_json("src", "default_settings");
					json.js[name] = default_json.js.at(name);
					json.save();
				}
				else
				{
					std::cout << err.what() << "\n";
					throw err;
				}
			}
		}

		volume = json.js.at(nameof(MusicVolume));
		auto &jsres = json.js.at(nameof(Resolution));
		resolution = { jsres[0], jsres[1] };
		window_mode = json.js.at(nameof(WindowMode));
		vsync = json.js.at(nameof(Vsync));
		frame_limit = json.js.at(nameof(FramerateLimit));
	}

	inline void Settings::resetToDefault()
	{
		json.js = engine::JsonFile("src", "default_settings.json").js;
		json.save();
	}
}
