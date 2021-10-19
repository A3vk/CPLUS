#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Command.h"
#include "Interpeter/Stack.h"

class CommandFactory
{
public:
	CommandFactory() = default;
	CommandFactory(const CommandFactory&) = default;
	CommandFactory& operator=(const CommandFactory&) { return *this; }
	~CommandFactory() = default;

	static std::unique_ptr<CommandFactory> Get()
	{
		static CommandFactory instance;
		return std::make_unique<CommandFactory>(instance);
	}

	template<typename T, typename... Args>
	void Register(Args... args)
	{
		m_Commands.push_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	std::shared_ptr<Command> Create(std::string line);
private:
	std::vector<std::shared_ptr<Command>> m_Commands;
};

