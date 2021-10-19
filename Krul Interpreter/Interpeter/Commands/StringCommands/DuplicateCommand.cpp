#include "DuplicateCommand.h"

#include "Exceptions/InterpreterException.h"

DuplicateCommand::DuplicateCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool DuplicateCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void DuplicateCommand::Execute(std::string& line)
{
	m_Stack->push_back(m_Stack->back());
}