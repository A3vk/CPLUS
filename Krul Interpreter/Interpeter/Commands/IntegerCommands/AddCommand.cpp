#include "AddCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

AddCommand::AddCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool AddCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void AddCommand::Execute(std::string& line)
{
	if(m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Add - The add command requires to have two values on the stack");
	}

	const int first = Helper::StringToInt(m_Stack->pop_back());
	const int second = Helper::StringToInt(m_Stack->pop_back());
	m_Stack->push_back(Helper::NumberToString(second + first));
}
