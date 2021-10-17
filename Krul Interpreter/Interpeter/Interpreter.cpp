#include "Interpreter.h"

#include <algorithm>
#include <iostream>
#include <sstream>

Interpreter::Interpreter()
{
	stack = std::make_shared<Stack<std::string>>();
	callStack = std::make_shared<Stack<int>>();
	variables = std::make_shared<std::map<std::string, std::string>>();
	labels = std::make_shared<std::map<std::string, int>>();
}

Interpreter::~Interpreter()
{
}

std::shared_ptr<InterpreterResult> Interpreter::Interpret(const std::string& file)
{
	const std::vector<std::string> lines = SplitLines(file);
	bool reachedEnd = false;

	// Get all reference assignments
	int index = 0;
	for (auto& line : lines)
	{
		if(line.rfind(':', 0) != std::string::npos)
		{
			labels->insert_or_assign(line.substr(1), index + 1);
		}
		++index;
	}

	for (lineNumber = 0; lineNumber < lines.size(); lineNumber++)
	{
		std::string currentLine = lines[lineNumber];

		// Comments
		if (currentLine.rfind('#', 0) != std::string::npos) continue;
		if (currentLine.rfind("end", 0) != std::string::npos)
		{
			reachedEnd = true;
			break;
		}

		// Values
		// Integer
		if (IsInt(currentLine))
		{
			stack->push_back(currentLine);
		}
		// String
		else if (currentLine.rfind('\\', 0) != std::string::npos)
		{
			stack->push_back(currentLine.substr(1));
		}
		// Labels
		// Assignment
		else if (currentLine.rfind(':', 0) != std::string::npos)
		{
			continue;
			//labels->insert_or_assign(currentLine.substr(1), lineNumber + 1);
		}
		// Reference
		else if (currentLine.rfind('>', 0) != std::string::npos)
		{
			// TODO: Check if variable exists!
			auto label = labels->find(currentLine.substr(1));
			stack->push_back(NumberToString(label->second));
		}
		// Variables
		// Assignment
		else if (currentLine.rfind('=', 0) != std::string::npos)
		{
			// TODO: Check if stack is not empty!
			variables->insert_or_assign(currentLine.substr(1), stack->pop_back());
		}
		// Reference
		else if (currentLine.rfind('$', 0) != std::string::npos)
		{
			stack->push_back(variables->at(currentLine.substr(1)));
		}
		// Integer operations
		// Add
		else if (currentLine.rfind("add", 0) != std::string::npos)
		{
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(first + second));
		}
		// Subtract
		else if (currentLine.rfind("sub", 0) != std::string::npos)
		{
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(first - second));
		}
		// Multiply
		else if (currentLine.rfind("mup", 0) != std::string::npos)
		{
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(first * second));
		}
		// Divide
		else if (currentLine.rfind("div", 0) != std::string::npos)
		{
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(first / second));
		}
		// Modulo
		else if (currentLine.rfind("mod", 0) != std::string::npos)
		{
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(first % second));
		}
		// Negate
		else if (currentLine.rfind("neg", 0) != std::string::npos)
		{
			const int value = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(value * -1));
		}
		// Absolute
		else if (currentLine.rfind("abs", 0) != std::string::npos)
		{
			const int value = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(std::abs(value)));
		}
		// Increment
		else if (currentLine.rfind("inc", 0) != std::string::npos)
		{
			const int value = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(value + 1));
		}
		// Decrement
		else if (currentLine.rfind("dec", 0) != std::string::npos)
		{
			const int value = StringToInt(stack->pop_back());
			stack->push_back(NumberToString(value - 1));
		}
		// String operations
		// Duplicate
		else if (currentLine.rfind("dup", 0) != std::string::npos)
		{
			stack->push_back(stack->back());
		}
		// Reverse
		else if (currentLine.rfind("rev", 0) != std::string::npos)
		{
			std::string value = stack->pop_back();
			std::reverse(value.begin(), value.end());
			stack->push_back(value);
		}
		// Substring
		else if (currentLine.rfind("slc", 0) != std::string::npos)
		{
			const int to = StringToInt(stack->pop_back());
			const int from = StringToInt(stack->pop_back());
			const std::string value = stack->pop_back();
			stack->push_back(value.substr(from, static_cast<size_t>(to) - from));
		}
		// Index
		else if (currentLine.rfind("idx", 0) != std::string::npos)
		{
			const int index = StringToInt(stack->pop_back());
			const std::string value = stack->pop_back();
			stack->push_back(CharToString(value.at(index)));
		}
		// Concatenation
		else if (currentLine.rfind("cat", 0) != std::string::npos)
		{
			const std::string first = stack->pop_back();
			const std::string second = stack->pop_back();
			stack->push_back(first + second);
		}
		// Length
		else if (currentLine.rfind("len", 0) != std::string::npos)
		{
			const std::string value = stack->pop_back();
			stack->push_back(NumberToString(value.length()));
		}
		// Rotate
		else if (currentLine.rfind("rot", 0) != std::string::npos)
		{
			std::string value = stack->pop_back();
			std::transform(value.begin(), value.end(), value.begin(), [](const char c) -> char
			{
				if (!std::isalpha(c)) return c;

				const char pivot = std::isupper(c) ? 'A' : 'a';
				return (c - pivot + 13) % 26 + pivot;
			});
			stack->push_back(value);
		}
		// Add new line
		else if (currentLine.rfind("enl", 0) != std::string::npos)
		{
			const std::string value = stack->pop_back();
			stack->push_back(value + "\n");
		}
		// Tests & Jumps
		// Goto
		else if (currentLine.rfind("gto", 0) != std::string::npos)
		{
			const int line = StringToInt(stack->pop_back());
			lineNumber = line;
		}
		// Goto if equal
		else if (currentLine.rfind("geq", 0) != std::string::npos)
		{
			const int line = StringToInt(stack->pop_back());
			const std::string first = stack->pop_back();
			const std::string second = stack->pop_back();
			if (first == second)
			{
				lineNumber = line;
			}
		}
		// Goto if not equal
		else if (currentLine.rfind("gne", 0) != std::string::npos)
		{
			const int line = StringToInt(stack->pop_back());
			const std::string first = stack->pop_back();
			const std::string second = stack->pop_back();
			if (first != second)
			{
				lineNumber = line;
			}
		}
		// Goto if less
		else if (currentLine.rfind("glt", 0) != std::string::npos)
		{
			const int line = StringToInt(stack->pop_back());
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			if (first < second)
			{
				lineNumber = line;
			}
		}
		// Goto if less or equal
		else if (currentLine.rfind("gle", 0) != std::string::npos)
		{
			const int line = StringToInt(stack->pop_back());
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			if (first <= second)
			{
				lineNumber = line;
			}
		}
		// Goto if greater
		else if (currentLine.rfind("ggt", 0) != std::string::npos)
		{
			const int line = StringToInt(stack->pop_back());
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			if (first > second)
			{
				lineNumber = line;
			}
		}
		// Goto if greater or equal
		else if (currentLine.rfind("gge", 0) != std::string::npos)
		{
			const int line = StringToInt(stack->pop_back());
			const int first = StringToInt(stack->pop_back());
			const int second = StringToInt(stack->pop_back());
			if (first >= second)
			{
				lineNumber = line;
			}
		}
		// Functions
		// Definition
		else if (currentLine.rfind("fun", 0) != std::string::npos)
		{
			callStack->push_back(lineNumber + 1);

			const int line = StringToInt(stack->pop_back());
			lineNumber = line;
		}
		// Return
		else if (currentLine.rfind("dup", 0) != std::string::npos)
		{
			lineNumber = callStack->pop_back();
		}
		// End
		else if (currentLine.rfind("dup", 0) != std::string::npos)
		{
			reachedEnd = true;
		}
		else
		{
			std::cout << "Unknown syntax: " + currentLine << std::endl;
		}
	}
	
	return std::make_shared<InterpreterResult>(stack->back(), reachedEnd);
}

std::vector<std::string> Interpreter::SplitLines(const std::string& input)
{
	std::vector<std::string> lines;
	std::stringstream stream(input);
	std::string line;

	while(std::getline(stream, line, '\n'))
	{
		lines.push_back(line);
	}

	return lines;
}

bool Interpreter::IsInt(const std::string& value)
{
	return !value.empty() && std::all_of(value.begin(), value.end(), std::isdigit);
}

std::string Interpreter::CharToString(char value)
{
	return std::string(1, value);
}

int Interpreter::StringToInt(const std::string& value)
{
	return std::stoi(value);
}
