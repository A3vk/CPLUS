#include <iostream>
#include <curl/curl.h>

#include "Application.h"
#include "Curl/CurlFacade.h"

int main()
{
    CurlFacade* curl = new CurlFacade();
    Application* application = new Application();
    std::string file = curl->Get("https://www.swiftcoder.nl/cplus/start.txt");
    //CURL* curl = curl_easy_init();
    std::cout << file << std::endl;

    application->InterpretMultipleOnlineFiles("https://www.swiftcoder.nl/cplus/start.txt");

    delete curl;
    delete application;
}