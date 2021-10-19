#include "GotoIfEqualCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

GotoIfEqualCommand::GotoIfEqualCommand(std::shared_ptr<Stack<std::string>> stack, size_t* lineNumber) : m_Stack(stack), m_LineNumber(lineNumber) {}

bool GotoIfEqualCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void GotoIfEqualCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("GotoIfEqual - The geq command requires to have three values on the stack");
	}

	const int lineNumber = Helper::StringToInt(m_Stack->pop_back());
	const std::string first = m_Stack->pop_back();
	const std::string second = m_Stack->pop_back();
	if (first == second)
	{
		*m_LineNumber = lineNumber;
	}
}