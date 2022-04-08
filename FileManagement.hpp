#include <fstream>
#include <windows.h>

enum class Settings
{
	Resolution, Vsync, FrameLimit
};


std::vector<std::string> getFileContent(std::ifstream &infile)
{
	if (infile.is_open())
	{		
		std::vector<std::string> buf;
		std::string line = "";
		while (!infile.eof())
		{
			std::getline(infile, line);
			buf.push_back(line);
		}
		return buf;
	}
	return {};
}


void create_infof()
{
	using std::string;
	using std::to_string;
	std::vector<string> props = { "resolution", "vsync", "frame-limit" };
	std::ofstream ofile;
	system("mkdir local");
	ofile.open("local/info.txt");
	std::vector<string> params = { to_string(GetSystemMetrics(SM_CXSCREEN)) + " " + to_string(GetSystemMetrics(SM_CYSCREEN)), "1", "60" }; // parametrs
	for (int i = 0; i < props.size(); i++)
		ofile << params[i] << ";" << props[i] << "\n";
	ofile.close();
}
std::vector<int> get_infof()
{ // reading file
	/*
	* 0 - resolution x
	* 1 - resolution y
	* 2 - boolean vsync
	* 3 - frame-limit
	*/
	using std::string;
	using std::to_string;
	std::ifstream ifile;
	ifile.open("local/info.txt"); // opening info file
	if (!ifile.is_open())
	{
		create_infof();
		ifile.open("local/info.txt");
	}
	auto buf = getFileContent(ifile);
	ifile.close();
	string str;
	std::vector<int> opt; // massive size is number of parametrs
	std::vector<string> props = { "resolution", "vsync", "frame-limit" }; // properties
	for (auto &i : buf)
	{
		str = "";
		for (auto ch : i)
		{
			if (ch == ' ')
			{
				opt.push_back(std::stoi(str));
				str = "";
			}
			else if (ch == ';')
			{
				opt.push_back(std::stoi(str));
				break;
			}
			else
				str += ch;
		}
	}
	return opt;
}

void resetInfoResolution(const unsigned int &x, const unsigned int &y)
{
	const std::string name = "resolution";
	const std::string str = std::to_string(x) + " " + std::to_string(y);
	std::ifstream ifile;
	ifile.open("local/info.txt");
	if (!ifile.is_open())
	{
		create_infof();
		ifile.open("local/info.txt");
	}
	auto buf = getFileContent(ifile);
	ifile.close();
	size_t n = -1;
	size_t k = -1;
	for (size_t i = 0; i < buf.size(); i++)
	{
		k = buf[i].find(name);
		if (k != -1)
		{
			n = i;
			break;
		}
	}
	if (n != -1)
	{
		std::string s = buf[n].substr(k, buf[n].size());
		buf[n] = str + ";" + s;
		std::ofstream outf;
		outf.open("local/info.txt");
		for (auto &i : buf)
			outf << i + "\n";
		outf.close();
	}
}
void resetInfoFrameLimit(const unsigned int &lim)
{
	const std::string name = "frame-limit";
	const std::string str = std::to_string(lim);
	std::ifstream ifile;
	ifile.open("local/info.txt");
	if (!ifile.is_open())
	{
		create_infof();
		ifile.open("local/info.txt");
	}
	auto buf = getFileContent(ifile);
	ifile.close();
	size_t n = -1;
	size_t k = -1;
	for (size_t i = 0; i < buf.size(); i++)
	{
		k = buf[i].find(name);
		if (k != -1)
		{
			n = i;
			break;
		}
	}
	if (n != -1)
	{
		std::string s = buf[n].substr(k, buf[n].size());
		buf[n] = str + ";" + s;
		std::ofstream outf;
		outf.open("local/info.txt");
		for (auto &i : buf)
			outf << i + "\n";
		outf.close();
	}
}
void resetInfoVsync(const bool &b)
{
	const std::string name = "vsync";
	const std::string str = std::to_string(b);
	std::ifstream ifile;
	ifile.open("local/info.txt");
	if (!ifile.is_open())
	{
		create_infof();
		ifile.open("local/info.txt");
	}
	auto buf = getFileContent(ifile);
	ifile.close();
	size_t n = -1;
	size_t k = -1;
	for (size_t i = 0; i < buf.size(); i++)
	{
		k = buf[i].find(name);
		if (k != -1)
		{
			n = i;
			break;
		}
	}
	if (n != -1)
	{
		std::string s = buf[n].substr(k, buf[n].size());
		buf[n] = str + ";" + s;
		std::ofstream outf;
		outf.open("local/info.txt");
		for (auto &i : buf)
			outf << i + "\n";
		outf.close();
	}
}