#pragma once
#include "Interpeter/Commands/Command.h"

class LabelDefinitionCommand : public Command
{
	const std::string syntax = ":";
public:
	LabelDefinitionCommand();
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
};

