#include "ConcatenationCommand.h"

#include "Exceptions/InterpreterException.h"

ConcatenationCommand::ConcatenationCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool ConcatenationCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void ConcatenationCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Concatenation - The cat command requires to have two values on the stack");
	}

	const std::string first = m_Stack->pop_back();
	const std::string second = m_Stack->pop_back();
	m_Stack->push_back(second + first);
}