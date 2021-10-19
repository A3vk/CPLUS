#include "DivideCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"
#include <cmath>

DivideCommand::DivideCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool DivideCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void DivideCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Divide - The div command requires to have two values on the stack");
	}
	
	const int first = Helper::StringToInt(m_Stack->pop_back());
	const int second = Helper::StringToInt(m_Stack->pop_back());

	if(first == 0)
	{
		throw InterpreterException("Divide - Divide by zero is not allowed");
	}
	
	m_Stack->push_back(Helper::NumberToString(static_cast <int>(std::floor(second / first))));
}