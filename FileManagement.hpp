#include <fstream>
#include <windows.h>
#include <nlohmann/json.hpp>


class JsonFile
{
	using Json = nlohmann::json;
	std::string path;
	std::string file_name;
	static void create(std::string path, std::string fname);
	static std::string getFullPath(const std::string &path, const std::string fname)
	{
		const char &lchar = path[path.size() - 1];
		return (lchar == '/' or lchar == '\\' ? path.substr(path.size() - 1) : path) + "\\" + fname + ".json";
	}
public:
	Json js;
	JsonFile(const std::string dir, const std::string fname, const Json j = Json()) : path(dir), file_name(fname), js(j) {}
	static Json load(std::string path, const std::string &fname); // loads json to file
	Json load();
	void save() const; // loads json to file
	static void save(std::string path, const std::string &fname, const Json &j = Json()); // loads json to file
};

void JsonFile::create(std::string path, std::string fname)
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

nlohmann::json JsonFile::load(std::string path, const std::string &fname)
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

nlohmann::json JsonFile::load()
{
	return js = JsonFile::load(path, file_name);
}

void JsonFile::save(std::string path, const std::string &fname, const Json &j)
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


void JsonFile::save() const
{
	save(path, file_name, js);
}

void create_infof()
{
	JsonFile jsf("src", "settings");
	jsf.js["Resolution"] = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	jsf.js["Vsync"] = true;
	jsf.js["Frame-limit"] = 60;
	jsf.save();
}

nlohmann::json load_infof()
{ // reading file
	std::ifstream infile;
	infile.open("src/settings.json");
	if (!infile.is_open())
		create_infof();
	else infile.close();
	return JsonFile::load("src", "settings");
}


void resetInfoResolution(const unsigned int &x, const unsigned int &y)
{
	JsonFile jsf = { "src", "settings", load_infof() };
	jsf.js["Resolution"] = { x, y };
	jsf.save();
}
void resetInfoFrameLimit(const unsigned int &lim)
{
	JsonFile jsf = { "src", "settings", load_infof() };
	jsf.js["Frame-limit"] = lim;
	jsf.save();
}
void resetInfoVsync(const bool &b)
{
	JsonFile jsf = { "src", "settings", load_infof() };
	jsf.js["Vsync"] = b;
	jsf.save();
}