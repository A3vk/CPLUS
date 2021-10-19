#pragma once
#include <memory>
#include <string>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class GotoCommand : public Command
{
	const std::string syntax = "gto";
	const size_t numberOfParameters = 1;
public:
	GotoCommand(std::shared_ptr<Stack<std::string>> stack, size_t* lineNumber);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
	size_t* m_LineNumber;
};

