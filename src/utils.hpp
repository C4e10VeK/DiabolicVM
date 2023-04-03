#ifndef DVM_UTILS_HPP
#define DVM_UTILS_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include <streambuf>

namespace dialang::utils
{
	template<typename T>
	inline std::string toString(T value)
	{
		return "";
	}
	
	template<>
	inline std::string toString<std::string>(std::string value)
	{
		return value;
	}
	
	template<>
	inline std::string toString<int32_t>(int32_t value)
	{
		return std::to_string(value);
	}
	
	template<>
	inline std::string toString<int64_t>(int64_t value)
	{
		return std::to_string(value);
	}

	inline bool readFile(const std::filesystem::path &path, std::string &text)
	{
		if (!std::filesystem::exists(path))
			return false;

		std::ifstream file(path);

		if (!file.is_open())
			return false;

		text = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		file.close();

		return true;
	}
}

#endif // DVM_UTILS_HPP
