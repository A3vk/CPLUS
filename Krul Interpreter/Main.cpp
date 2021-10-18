#include <iostream>
#include <curl/curl.h>

#include "Application.h"
#include "Curl/CurlFacade.h"

int main()
{
    Application* application = new Application();

    // Manual
    std::cout << "========= Handmatig =========" << std::endl;
    application->InterpretOnlineFile("start.txt");
    application->InterpretOnlineFile("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt");
    application->InterpretOnlineFile("4812-9-6727.txt");
    application->InterpretOnlineFile("AasHgsho.txt");
    application->InterpretOnlineFile("Bososen-hosgen-in-warme-losden-aos-de-bososenboom.txt");
    application->InterpretOnlineFile("we-zijn-er-bijna.txt");
    application->InterpretOnlineFile("ninaf-zvabe-fjn-pcc1.txt");
	
    // Automatic
    std::cout << "\n\n========= Automatisch =========" << std::endl;
    const std::string result = application->InterpretMultipleOnlineFiles("start.txt");
    std::cout << "\n========= Resultaat =========" << std::endl;
    std::cout << result << std::endl;
    delete application;
}