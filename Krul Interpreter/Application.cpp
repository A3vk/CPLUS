#include "Application.h"

#include "Interpeter/Interpreter.h"

Application::Application()
{
	m_CurlFacade = std::make_unique<CurlFacade>();
	m_Interpreter = std::make_unique<Interpreter>();
}

std::string Application::InterpretOnlineFile(const std::string& url)
{
	std::string file = m_CurlFacade->Get(url);
	return "";
}

std::string Application::InterpretMultipleOnlineFiles(const std::string& url)
{
	std::shared_ptr<InterpreterResult> result(new InterpreterResult());

	while(!result->ReachedEnd)
	{
		result = m_Interpreter->Interpret(url);
		
	}

	return result->Result;
}
