#include "Application.h"

#include <iostream>

#include "Interpeter/Interpreter.h"

Application::Application()
{
	m_CurlFacade = std::make_unique<CurlFacade>();
	m_Interpreter = std::make_unique<Interpreter>();
}

std::string Application::InterpretOnlineFile(const std::string& file)
{
	std::string fileData = m_CurlFacade->Get(BASE_URL + file);
	const std::shared_ptr<InterpreterResult> result = m_Interpreter->Interpret(fileData);
	std::cout << "Enkel bestand uitvoeren, resulataat: " + result->Result << std::endl;
	return result->Result;
}

std::string Application::InterpretMultipleOnlineFiles(const std::string& file)
{
	std::shared_ptr<InterpreterResult> result(new InterpreterResult());
	std::string currentFile = file;

	std::cout << "Meerdere bestanden uitvoeren, startpunt: " + file << std::endl;
	
	while(!result->ReachedEnd)
	{
		std::string fileData = m_CurlFacade->Get(BASE_URL + currentFile);
		result = m_Interpreter->Interpret(fileData);
		currentFile = result->Result;
		std::cout << currentFile << std::endl;
	}

	return result->Result;
}
