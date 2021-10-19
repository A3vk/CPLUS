#include "AbsoluteCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

AbsoluteCommand::AbsoluteCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool AbsoluteCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void AbsoluteCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Absolute - The abs command requires to have one value on the stack");
	}

	const int value = Helper::StringToInt(m_Stack->pop_back());
	m_Stack->push_back(Helper::NumberToString(std::abs(value)));
}
