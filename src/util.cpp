#include "util.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "physfs.hpp"

std::string util::read_file(std::string path)
{
	PhysFS::ifstream f(path);
	f.seekg(0, f.end);
	size_t sz = f.tellg();
	f.seekg(0, f.beg);
	std::string s;
	s.resize(sz);
	char *s_buf = &s[0];

	f.read(s_buf, sz);

	return s;
}

std::vector<unsigned char> util::read_file_bytes(std::string path)
{
	PhysFS::ifstream f(path);
	f.seekg(0, f.end);
	size_t sz = f.tellg();
	f.seekg(0, f.beg);

	std::vector<unsigned char> dat;
	dat.resize(sz);
	char *dat_buf = (char*)&dat[0];

	f.read(dat_buf, sz);

	return dat;
}

std::vector<std::string> util::split(const std::string& s, const std::string& delim, const bool keep_empty)
{
	std::vector<std::string> result;
	if (delim.empty())
	{
		result.push_back(s);
		return result;
	}
	std::string::const_iterator substart = s.begin(), subend;
	while (true)
	{
		subend = std::search(substart, s.end(), delim.begin(), delim.end());
		std::string temp(substart, subend);
		if (keep_empty || !temp.empty())
		{
			result.push_back(temp);
		}
		if (subend == s.end())
		{
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}
