#include "FunctionDefinitionCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

FunctionDefinitionCommand::FunctionDefinitionCommand(std::shared_ptr<Stack<std::string>> stack, std::shared_ptr<Stack<int>> callStack, size_t* lineNumber) : m_Stack(stack), m_CallStack(callStack), m_LineNumber(lineNumber) {}

bool FunctionDefinitionCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void FunctionDefinitionCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("FunctionDefinition - The fun command requires to have one value on the stack");
	}
	
	m_CallStack->push_back(*m_LineNumber);

	const int lineNumber = Helper::StringToInt(m_Stack->pop_back());
	*m_LineNumber = lineNumber;
}