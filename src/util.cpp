#include "util.h"
#include <string>
#include <fstream>

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