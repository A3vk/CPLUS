#include "VariableReferenceCommand.h"

#include "Exceptions/InterpreterException.h"

VariableReferenceCommand::VariableReferenceCommand(std::shared_ptr<Stack<std::string>> stack, std::shared_ptr<std::map<std::string, std::string>> variables) : m_Stack(stack), m_Variables(variables) {}

bool VariableReferenceCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void VariableReferenceCommand::Execute(std::string& line)
{
	auto variable = m_Variables->find(line.substr(1));
	if (variable == m_Variables->end())
	{
		throw InterpreterException("Label - The label is not defined (" + line.substr(1) + ")");
	}
	m_Stack->push_back(m_Variables->at(line.substr(1)));
}