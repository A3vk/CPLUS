#include <iostream>
#include <curl/curl.h>

#include "Application.h"
#include "Curl/CurlFacade.h"

int main(int argc, char* argv[])
{
    std::string file = "start.txt";
	
	if (argc <= 1)
	{
        std::cout << "No file parameter found, using the default file 'start.txt'" << std::endl;
	} else
	{
        file = argv[1];
	}
	
    Application application;
    
    //std::cout << "========= Handmatig =========" << std::endl;
    //application->InterpretOnlineFile("start.txt");
    //application.InterpretOnlineFile("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.txt");
    //application->InterpretOnlineFile("4812-9-6727.txt");
    //application->InterpretOnlineFile("AasHgsho.txt");
    //application->InterpretOnlineFile("Bososen-hosgen-in-warme-losden-aos-de-bososenboom.txt");
    //application->InterpretOnlineFile("we-zijn-er-bijna.txt");
    //application->InterpretOnlineFile("ninaf-zvabe-fjn-pcc1.txt");

    std::cout << "Excecution results (" + file << "): " << std::endl;
    application.InterpretMultipleOnlineFiles(file);
	
    return 0;
}