#pragma once
#include <exception>
#include <string>

class CurlUrlException : public std::exception
{
public:
	CurlUrlException(const std::string& url) : exception(url.c_str()), m_Url(url) {}
	std::string GetException();
private:
	std::string m_Url;
};

