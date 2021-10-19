#include "VariableAssignmentCommand.h"

#include "Exceptions/InterpreterException.h"

VariableAssignmentCommand::VariableAssignmentCommand(std::shared_ptr<Stack<std::string>> stack, std::shared_ptr<std::map<std::string, std::string>> variables) : m_Stack(stack), m_Variables(variables) {}

bool VariableAssignmentCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void VariableAssignmentCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("VariableAssignment - The = command requires to have one value on the stack");
	}
	
	m_Variables->insert_or_assign(line.substr(1), m_Stack->pop_back());
}
