#include "CurlFacade.h"

CurlFacade::CurlFacade()
{
	m_Curl = std::unique_ptr<CURL, CurlDeleter>(curl_easy_init());
}

CurlFacade::~CurlFacade()
{
	curl_easy_cleanup(m_Curl.release());
}

size_t DataToString(char* contents, size_t size, size_t nmemb, std::string* userp)
{
	const size_t newLength = size * nmemb;
	userp->append(contents, newLength);
	return newLength;
}

std::string CurlFacade::Get(const std::string& url)
{
	std::string result;
	curl_easy_setopt(m_Curl.get(), CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_Curl.get(), CURLOPT_WRITEFUNCTION, DataToString);
	curl_easy_setopt(m_Curl.get(), CURLOPT_WRITEDATA, &result);
	curl_easy_perform(m_Curl.get());
	m_Curl.reset(curl_easy_init());
	return result;
}
