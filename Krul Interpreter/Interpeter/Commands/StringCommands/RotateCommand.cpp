#include "RotateCommand.h"

#include <algorithm>
#include "Exceptions/InterpreterException.h"

RotateCommand::RotateCommand(std::shared_ptr<Stack<std::string>> stack) : m_Stack(stack) {}

bool RotateCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void RotateCommand::Execute(std::string& line)
{
	if (m_Stack->size() < numberOfParameters)
	{
		throw InterpreterException("Rotate - The rot command requires to have one value on the stack");
	}

	std::string value = m_Stack->pop_back();
	std::transform(value.begin(), value.end(), value.begin(), [](const char c) -> char
		{
			if (!std::isalpha(c)) return c;

			const char pivot = std::isupper(c) ? 'A' : 'a';
			return (c - pivot + 13) % 26 + pivot;
		});
	m_Stack->push_back(value);
}