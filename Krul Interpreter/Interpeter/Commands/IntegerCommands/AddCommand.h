#pragma once
#include <memory>

#include "Interpeter/Commands/Command.h"
#include "Interpeter/Stack.h"

class AddCommand : public Command
{
	const std::string syntax = "add";
	const size_t numberOfParameters = 2;
public:
	AddCommand(std::shared_ptr<Stack<std::string>> stack);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
};

