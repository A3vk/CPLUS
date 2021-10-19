#pragma once
#include <memory>
#include <string>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class ModuloCommand : public Command
{
	const std::string syntax = "mod";
	const size_t numberOfParameters = 2;
public:
	ModuloCommand(std::shared_ptr<Stack<std::string>> stack);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
};

