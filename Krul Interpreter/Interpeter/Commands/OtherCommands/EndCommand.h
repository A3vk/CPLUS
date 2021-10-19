#pragma once
#include "Interpeter/Commands/Command.h"

class EndCommand : public Command
{
	const std::string syntax = "end";
public:
	EndCommand(bool* reachedEnd);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	bool* m_reachedEnd;
};

