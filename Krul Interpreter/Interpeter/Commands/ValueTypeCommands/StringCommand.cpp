#include "StringCommand.h"

#include "Exceptions/InterpreterException.h"

StringCommand::StringCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool StringCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void StringCommand::Execute(std::string& line)
{
	m_Stack->push_back(line.substr(1));
}