#pragma once
#include <memory>
#include <string>

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
	std::shared_ptr<InterpreterResult> Interpret(const std::string& file)
	{
		return std::make_shared<InterpreterResult>("Dit is het resultaat!", true);
	}
};
