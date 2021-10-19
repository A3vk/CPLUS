#include "NewLineCommand.h"

#include "Exceptions/InterpreterException.h"

NewLineCommand::NewLineCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool NewLineCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void NewLineCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("NewLine - The enl command requires to have one value on the stack");
	}

	const std::string value = m_Stack->pop_back();
	m_Stack->push_back(value + "\n");
}