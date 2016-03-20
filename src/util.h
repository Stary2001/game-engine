#pragma once
#include <memory>
#include <vector>
#include <string>

namespace util
{
	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
	    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	std::string read_file(std::string path);
	std::vector<unsigned char> read_file_bytes(std::string path);

	std::vector<std::string> split(const std::string& s, const std::string& delim, const bool keep_empty = true);
}