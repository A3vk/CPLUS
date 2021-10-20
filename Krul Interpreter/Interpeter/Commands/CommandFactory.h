#pragma once
#include <memory>
#include <vector>

#include "Command.h"

class CommandFactory
{
protected:
	static std::unique_ptr<CommandFactory> instance;
public:
	CommandFactory() = default;
	CommandFactory(const CommandFactory&) = delete;
	void operator=(const CommandFactory&) = delete;
	~CommandFactory();

	static std::unique_ptr<CommandFactory> GetInstance();

	template<typename T, typename... Args>
	void Register(Args... args)
	{
		m_Commands.push_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	std::shared_ptr<Command> Create(std::string line);
private:
	std::vector<std::shared_ptr<Command>> m_Commands;
};

