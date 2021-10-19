#include "ReverseCommand.h"

#include "Exceptions/InterpreterException.h"

ReverseCommand::ReverseCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool ReverseCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void ReverseCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Reverse - The rev command requires to have one value on the stack");
	}

	std::string value = m_Stack->pop_back();
	std::reverse(value.begin(), value.end());
	m_Stack->push_back(value);
}