#include "LabelDefinitionCommand.h"

LabelDefinitionCommand::LabelDefinitionCommand() = default;

bool LabelDefinitionCommand::IsCommand(std::string & line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void LabelDefinitionCommand::Execute(std::string & line) {}