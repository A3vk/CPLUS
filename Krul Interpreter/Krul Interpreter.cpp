#include <iostream>
#include <curl/curl.h>

int main()
{
    CURL* curl = curl_easy_init();
    std::cout << "HELLO" << std::endl;
}