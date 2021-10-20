#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Stack.h"
#include "Commands/CommandFactory.h"

struct InterpreterResult
{
	InterpreterResult() = default;
	InterpreterResult(std::string result, bool reachedEnd)
	{
		Result = result;
		ReachedEnd = reachedEnd;
	}

	std::string Result;
	bool ReachedEnd = false;
};

class Interpreter
{
public:
	Interpreter();
	~Interpreter() = default;
	
	std::shared_ptr<InterpreterResult> Interpret(const std::string& file);
private:
	void RegisterCommands();
	std::vector<std::string> SplitLines(const std::string& input) const;
	void CleanUp() const;

	size_t lineNumber = 0;
	bool reachedEnd = false;
	std::shared_ptr<Stack<std::string>> stack;
	std::shared_ptr<Stack<int>> callStack;
	std::shared_ptr<std::map<std::string, std::string>> variables;
	std::shared_ptr<std::map<std::string, int>> labels;
	std::unique_ptr<CommandFactory> m_Factory;
};
