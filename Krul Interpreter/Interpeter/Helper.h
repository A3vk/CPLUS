#pragma once
#include <string>

class Helper
{
public:
	static bool IsInt(const std::string& value);
	template<typename T>
	static std::string NumberToString(T value)
	{
		return std::to_string(value);
	}
	static std::string CharToString(char value);
	static int StringToInt(const std::string& value);
};

