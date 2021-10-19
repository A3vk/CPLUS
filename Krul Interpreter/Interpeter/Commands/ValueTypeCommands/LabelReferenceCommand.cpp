#include "LabelReferenceCommand.h"

#include "Exceptions/InterpreterException.h"
#include "Interpeter/Helper.h"

LabelReferenceCommand::LabelReferenceCommand(std::shared_ptr<Stack<std::string>> stack, std::shared_ptr<std::map<std::string, int>> labels) : m_Stack(stack), m_Labels(labels) {}

bool LabelReferenceCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void LabelReferenceCommand::Execute(std::string& line)
{
	auto label = m_Labels->find(line.substr(1));
	
	if (label == m_Labels->end())
	{
		throw InterpreterException("Label - The label is not defined (" + line.substr(1) + ")");
	}

	m_Stack->push_back(Helper::NumberToString(label->second));
}