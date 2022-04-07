#include <fstream>
#include <windows.h>

std::vector<int> get_infof()
{ // reading file
	using std::string;
	using std::to_string;
	std::ifstream ifile;
	std::vector<string> buf;
	ifile.open("local/info.txt"); // opening info file
	std::vector<string> props = { "resolution", "vsync", "frame-limit" }; // properties
	if (!ifile.is_open())
	{
		std::ofstream ofile;
		system("mkdir local");
		ofile.open("local/info.txt");
		std::vector<string> params = {to_string(GetSystemMetrics(SM_CXSCREEN)) + " " + to_string(GetSystemMetrics(SM_CYSCREEN)), "1", "60"}; // parametrs
		for(int i = 0; i < props.size(); i++)
			ofile << params[i] << ";" << props[i] << "\n";
		ofile.close();
		ifile.open("local/info.txt");
	}
	string *line = new string();
	while (!ifile.eof())
	{
		std::getline(ifile, *line);
		buf.push_back(*line);
	}
	delete line;
	ifile.close();
	string str;
	std::vector<int> opt; // massive size is number of parametrs
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
