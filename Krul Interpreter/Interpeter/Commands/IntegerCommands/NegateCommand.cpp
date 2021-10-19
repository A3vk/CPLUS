#include "NegateCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

NegateCommand::NegateCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool NegateCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void NegateCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Negate - The neg command requires to have one value on the stack");
	}

	const int value = Helper::StringToInt(m_Stack->pop_back());
	m_Stack->push_back(Helper::NumberToString(value * -1));
}