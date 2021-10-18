#pragma once
#include <memory>

#include "Curl/CurlFacade.h"
#include "Interpeter/Interpreter.h"

#define BASE_URL "https://www.swiftcoder.nl/cplus/"

class Application
{
public:
	Application();
	~Application() = default;
	
	std::string InterpretOnlineFile(const std::string& file);
	std::string InterpretMultipleOnlineFiles(const std::string& file);
private:
	std::unique_ptr<CurlFacade> m_CurlFacade;
	std::unique_ptr<Interpreter> m_Interpreter;
};

