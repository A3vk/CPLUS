#include "IntegerCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

IntegerCommand::IntegerCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool IntegerCommand::IsCommand(std::string& line)
{
	return Helper::IsInt(line);
}

void IntegerCommand::Execute(std::string& line)
{
	m_Stack->push_back(line);
}