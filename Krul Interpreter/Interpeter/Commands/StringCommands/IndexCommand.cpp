#include "IndexCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

IndexCommand::IndexCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool IndexCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void IndexCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Index - The idx command requires to have two values on the stack");
	}

	const int index = Helper::StringToInt(m_Stack->pop_back());
	const std::string value = m_Stack->pop_back();
	m_Stack->push_back(Helper::CharToString(value.at(index)));
}