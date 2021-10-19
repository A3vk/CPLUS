#include "SubstringCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

SubstringCommand::SubstringCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool SubstringCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void SubstringCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Substring - The sub command requires to have three value on the stack");
	}

	const int to = Helper::StringToInt(m_Stack->pop_back());
	const int from = Helper::StringToInt(m_Stack->pop_back());
	const std::string value = m_Stack->pop_back();
	m_Stack->push_back(value.substr(from, static_cast<size_t>(to) - from));
}