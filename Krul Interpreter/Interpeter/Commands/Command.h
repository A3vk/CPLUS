#pragma once
#include <string>

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	
	virtual  bool IsCommand(std::string& line) = 0;
	virtual void Execute(std::string& line) = 0;
};

