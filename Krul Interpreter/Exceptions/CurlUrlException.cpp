#include "CurlUrlException.h"

std::string CurlUrlException::GetException()
{
	return "Invalid URL: " + m_Url;
}
