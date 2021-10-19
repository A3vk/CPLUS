#include "FunctionReturnCommand.h"

#include "Exceptions/InterpreterException.h"

FunctionReturnCommand::FunctionReturnCommand(std::shared_ptr<Stack<int>> callStack, size_t* lineNumber) : m_CallStack(callStack), m_LineNumber(lineNumber) {}

bool FunctionReturnCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void FunctionReturnCommand::Execute(std::string& line)
{
	if (m_CallStack->size() < numberOfParameters)
	{
		throw InterpreterException("FunctionReturn - The ret command requires to have one value on the call stack");
	}

	*m_LineNumber = m_CallStack->pop_back();
}