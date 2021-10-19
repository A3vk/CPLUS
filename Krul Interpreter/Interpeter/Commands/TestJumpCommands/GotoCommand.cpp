#include "GotoCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

GotoCommand::GotoCommand(std::shared_ptr<Stack<std::string>> stack, size_t* lineNumber) : m_Stack(stack), m_LineNumber(lineNumber) {}

bool GotoCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void GotoCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Goto - The gto command requires to have one value on the stack");
	}

	const int lineNumber = Helper::StringToInt(m_Stack->pop_back());
	*m_LineNumber = lineNumber;
}