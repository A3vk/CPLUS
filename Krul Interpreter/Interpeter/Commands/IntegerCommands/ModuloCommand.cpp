#include "ModuloCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

ModuloCommand::ModuloCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool ModuloCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void ModuloCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Modulo - The mod command requires to have two value on the stack");
	}

	const int first = Helper::StringToInt(m_Stack->pop_back());
	const int second = Helper::StringToInt(m_Stack->pop_back());
	m_Stack->push_back(Helper::NumberToString(second % first));
}