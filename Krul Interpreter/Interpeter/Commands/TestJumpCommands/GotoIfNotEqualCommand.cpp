#include "GotoIfNotEqualCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

GotoIfNotEqualCommand::GotoIfNotEqualCommand(std::shared_ptr<Stack<std::string>> stack, size_t* lineNumber) : m_Stack(stack), m_LineNumber(lineNumber) {}

bool GotoIfNotEqualCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void GotoIfNotEqualCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("GotoIfNotEqual - The gne command requires to have three values on the stack");
	}

	const int lineNumber = Helper::StringToInt(m_Stack->pop_back());
	const std::string first = m_Stack->pop_back();
	const std::string second = m_Stack->pop_back();
	if (first != second)
	{
		*m_LineNumber = lineNumber;
	}
}