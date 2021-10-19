#pragma once
#include <memory>
#include <string>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class FunctionDefinitionCommand : public Command
{
	const std::string syntax = "fun";
	const size_t numberOfParameters = 1;
public:
	FunctionDefinitionCommand(std::shared_ptr<Stack<std::string>> stack, std::shared_ptr<Stack<int>> callStack, size_t* lineNumber);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
	std::shared_ptr<Stack<int>> m_CallStack;
	size_t* m_LineNumber;
};

