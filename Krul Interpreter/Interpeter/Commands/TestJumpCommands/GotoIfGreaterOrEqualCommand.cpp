#include "GotoIfGreaterOrEqualCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

GotoIfGreaterOrEqualCommand::GotoIfGreaterOrEqualCommand(std::shared_ptr<Stack<std::string>> stack, size_t* lineNumber) : m_Stack(stack), m_LineNumber(lineNumber) {}

bool GotoIfGreaterOrEqualCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void GotoIfGreaterOrEqualCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("GotoIfGreaterOrEqual - The gge command requires to have three values on the stack");
	}

	const int lineNumber = Helper::StringToInt(m_Stack->pop_back());
	const int second = Helper::StringToInt(m_Stack->pop_back());
	const int first = Helper::StringToInt(m_Stack->pop_back());
	if (first >= second)
	{
		*m_LineNumber = lineNumber;
	}
}