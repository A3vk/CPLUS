#include "Application.h"

#include <iostream>

#include "Exceptions/CurlUrlException.h"
#include "Interpeter/Interpreter.h"

Application::Application()
{
	m_CurlFacade = std::make_unique<CurlFacade>();
	m_Interpreter = std::make_unique<Interpreter>();
}

std::string Application::InterpretOnlineFile(const std::string& file)
{
	std::string fileData;
	
	try
	{
		fileData = m_CurlFacade->Get(BASE_URL + file);
	}
	catch (CurlUrlException& e)
	{
		std::cout << e.GetException() << std::endl;
		return "";
	}
	
	const std::shared_ptr<InterpreterResult> result = m_Interpreter->Interpret(fileData);
	std::cout << result->Result << std::endl;
	return result->Result;
}

std::string Application::InterpretMultipleOnlineFiles(const std::string& file)
{
	std::shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();
	std::string currentFile = file;
		
	while(!result->ReachedEnd)
	{
		std::string fileData;
		try
		{
			fileData = m_CurlFacade->Get(BASE_URL + currentFile);
		}
		catch (CurlUrlException& e)
		{
			std::cout << e.GetException() << std::endl;
			return "";
		}
		
		result = m_Interpreter->Interpret(fileData);
		currentFile = result->Result;
		std::cout << currentFile << std::endl;
	}

	return result->Result;
}
