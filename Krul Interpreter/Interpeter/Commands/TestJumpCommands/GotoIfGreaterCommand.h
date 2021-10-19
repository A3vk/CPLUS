#pragma once
#include <memory>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class GotoIfGreaterCommand : public Command
{
	const std::string syntax = "ggt";
	const size_t numberOfParameters = 3;
public:
	GotoIfGreaterCommand(std::shared_ptr<Stack<std::string>> stack, size_t* lineNumber);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
	size_t* m_LineNumber;
};

