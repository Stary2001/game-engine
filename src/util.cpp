#include "util.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

std::string util::read_file(std::string path)
{
	std::ifstream f(path, std::ifstream::in | std::ifstream::binary);
	f.seekg(0, f.end);
	size_t sz = f.tellg();
	f.seekg(0, f.beg);
	std::string s;
	s.resize(sz);
	char *s_buf = &s[0];

	f.read(s_buf, sz);

	return s;
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
