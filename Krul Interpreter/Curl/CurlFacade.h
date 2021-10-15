#pragma once

#include <curl/curl.h>
#include <memory>
#include <string>

struct CurlDeleter {
	void operator()(CURL* curl) const
	{
		if (curl) curl_easy_cleanup(curl);
	}
};

class CurlFacade
{
public:	
	CurlFacade();
	~CurlFacade();
	std::string Get(const std::string& url);	
private:
	std::unique_ptr<CURL, CurlDeleter> m_Curl;
};

