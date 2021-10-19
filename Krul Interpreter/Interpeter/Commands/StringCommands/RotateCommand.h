#pragma once
#include <memory>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class RotateCommand : public Command
{
	const std::string syntax = "rot";
	const size_t numberOfParameters = 1;
public:
	RotateCommand(std::shared_ptr<Stack<std::string>> stack);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
};

