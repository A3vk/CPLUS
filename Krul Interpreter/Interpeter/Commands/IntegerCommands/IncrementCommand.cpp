#include "IncrementCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

IncrementCommand::IncrementCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool IncrementCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void IncrementCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Increment - The inc command requires to have one value on the stack");
	}

	const int value = Helper::StringToInt(m_Stack->pop_back());
	m_Stack->push_back(Helper::NumberToString(value + 1));
}