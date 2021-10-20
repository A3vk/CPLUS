#include "CommandFactory.h"

#include "Exceptions/InterpreterException.h"

CommandFactory::~CommandFactory()
{
	//m_Commands.clear();
}

std::unique_ptr<CommandFactory> CommandFactory::instance = nullptr;

std::unique_ptr<CommandFactory> CommandFactory::GetInstance()
{
	if(instance == nullptr)
	{
		instance = std::make_unique<CommandFactory>();
	}

	return std::move(instance);
}

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
