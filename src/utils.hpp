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

	inline std::string readFile(const std::filesystem::path &path)
	{
		std::ifstream file(path);

		std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		file.close();

		return text;
	}
}

#endif // DVM_UTILS_HPP
