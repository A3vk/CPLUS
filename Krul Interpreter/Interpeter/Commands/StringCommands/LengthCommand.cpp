#include "LengthCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

LengthCommand::LengthCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool LengthCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void LengthCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Length - The len command requires to have one value on the stack");
	}

	const std::string value = m_Stack->pop_back();
	m_Stack->push_back(Helper::NumberToString(value.length()));
}