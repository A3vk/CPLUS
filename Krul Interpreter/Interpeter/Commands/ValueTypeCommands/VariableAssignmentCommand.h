#pragma once
#include <memory>
#include <string>
#include <map>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class VariableAssignmentCommand : public Command
{
	const std::string syntax = "=";
	const size_t numberOfParameters = 1;
public:
	VariableAssignmentCommand(std::shared_ptr<Stack<std::string>> stack, std::shared_ptr<std::map<std::string, std::string>> variables);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
	std::shared_ptr<std::map<std::string, std::string>> m_Variables;
};

