#pragma once
#include <memory>
#include <string>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class FunctionReturnCommand : public Command
{
	const std::string syntax = "ret";
	const size_t numberOfParameters = 1;
public:
	FunctionReturnCommand(std::shared_ptr<Stack<int>> stack, size_t* lineNumber);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<int>> m_CallStack;
	size_t* m_LineNumber;
};

