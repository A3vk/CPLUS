#include "CommandFactory.h"

#include "Exceptions/InterpreterException.h"

std::shared_ptr<Command> CommandFactory::Create(std::string line)
{
	for (auto& command : m_Commands)
	{
		if (command->IsCommand(line))
		{
			return command;
		}
	}

	throw InterpreterException("Syntax unknown! The syntax from this line is not known by the interpreter: " + line);
}
