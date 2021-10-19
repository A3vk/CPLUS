#include "Helper.h"

#include <algorithm>

bool Helper::IsInt(const std::string& value)
{
	return !value.empty() && std::all_of(value.begin(), value.end(), std::isdigit);
}

std::string Helper::CharToString(char value)
{
	return std::string(1, value);
}

int Helper::StringToInt(const std::string& value)
{
	return std::stoi(value);
}