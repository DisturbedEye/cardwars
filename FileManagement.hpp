#pragma once

#include <fstream>
#include <windows.h>


class engine::JsonFile
{
	using Json = nlohmann::json;
	std::string path;
	std::string file_name;
	static void create(std::string path, std::string fname);
	static std::string getFullPath(const std::string &path, const std::string fname)
	{
		if (path.size() == 0)
			return fname + ".json";
		const char &lchar = path[path.size() - 1];
		return (lchar == '/' or lchar == '\\' ? path.substr(path.size() - 1) : path) + "\\" + fname + ".json";
	}
public:
	Json js;
	JsonFile(const std::string dir, const std::string fname, const Json j = Json()) : path(dir), file_name(fname), js(j) {}
	static Json load(std::string path, const std::string &fname); // loads json to file
	static Json load(const JsonFile &jsonf); // loads json to file
	Json load();
	std::string getFileName() { return file_name; }
	std::string getPath() { return path; }
	
	void save() const; // loads json to file
	static void save(const JsonFile &jsonf);
	static void save(std::string path, const std::string &fname, const Json &j = Json()); // loads json to file
};

void engine::JsonFile::create(std::string path, std::string fname)
{
	using namespace std::string_literals;
	std::string com = "mkdir "s + path;
	system(com.c_str()); // console file creating (but only for windows)
	std::ofstream ofile;
	ofile.open(getFullPath(path, fname));
	if (!ofile.is_open())
	{
		std::cerr << "FileOpenErr: No such file or dirrectory\n";
		throw;
	}
	ofile.close();
}

nlohmann::json engine::JsonFile::load(std::string path, const std::string &fname)
{
	std::ifstream infile;
	const std::string full_path = getFullPath(path, fname);
	infile.open(full_path);
	if (!infile.is_open())
	{
		create(path, fname);
		infile.open(full_path);
	}
	std::string strjs = ""; // json dumped string
	std::string line;
	while (!infile.eof())
	{
		infile >> line;
		strjs += line;
	}
	infile.close();
	return Json::parse(strjs);
}

inline nlohmann::json engine::JsonFile::load(const JsonFile &jsonf)
{
	return load(jsonf.path, jsonf.file_name);
}

nlohmann::json engine::JsonFile::load()
{
	return js = JsonFile::load(path, file_name);
}

void engine::JsonFile::save(std::string path, const std::string &fname, const Json &j)
{
	std::ofstream outf;
	const std::string full_path = getFullPath(path, fname);
	outf.open(full_path);
	if (!outf.is_open())
	{
		create(path, fname);
		outf.open(full_path);
	}
	outf << j.dump(4, ' ');
	outf.close();
}


void engine::JsonFile::save() const
{
	save(path, file_name, js);
}

inline void engine::JsonFile::save(const JsonFile &jsonf)
{
	save(jsonf.path, jsonf.file_name, jsonf.js);
}

void engine::create_infof()
{
	JsonFile jsf("src", "settings");
	jsf.js["Resolution"] = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) }; // resolution
	jsf.js["Vsync"] = true; // vsync
	jsf.js["Framerate-limit"] = 60; // frame limit 
	jsf.js["Video-mode"] = 0; // window mode
	jsf.save();
}

nlohmann::json engine::load_infof()
{ // reading file
	std::ifstream infile;
	infile.open("src/settings.json");
	if (!infile.is_open())
		create_infof();
	else infile.close();
	auto js = JsonFile::load("src", "settings");
	try
	{
		std::vector<std::string> v = { "Resolution", "Vsync", "Framerate-limit", "Video-mode"};
		for (int i = 0; i < v.size(); i++)
			js.at(v[i]);
	}
	catch (Json::type_error &err)
	{
		if (err.id == 304)
		{
			create_infof();
			js = JsonFile::load("src", "settings");
		}
		else 
		{
			std::cout << err.what() << "\n";
			throw err;
		}
	}
	return js;
}


void engine::resetInfoResolution(const unsigned int x, const unsigned int y)
{
	Json js = load_infof();
	js["Resolution"] = { x, y };
	JsonFile::save("src", "settings", js);
}
void engine::resetInfoFramerateLimit(const unsigned int lim)
{
	Json js = load_infof();
	js["Framerate-limit"] = lim;
	JsonFile::save("src", "settings", js);
}
void engine::resetInfoVsync(const bool b)
{
	Json js = load_infof();
	js["Vsync"] = b;
	JsonFile::save("src", "settings", js);
}

void engine::resetInfoVideoMode(const int mode)
{
	Json js = load_infof();
	js["Video-mode"] = mode;
	JsonFile::save("src", "settings", js);
}


int engine::getInfoVideoMode()
{
	const Json js = load_infof();
	int mode = js.at("Video-mode");
	return video_modes[mode];
}

sf::Vector2u engine::getInfoResolution() 
{
	const Json js = load_infof();
	const auto arrv = js.at("Resolution");
	return Vec2u(arrv[0], arrv[1]);
}

unsigned int engine::getInfoFramerateLimit()
{
	const Json js = load_infof();
	const unsigned int a = js.at("Framerate-limit");
	return a;
}

bool engine::getInfoVsync()
{
	const Json js = load_infof();
	const bool a = js.at("Vsync");
	return a;
}


