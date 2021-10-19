#pragma once
#include "Interpeter/Commands/Command.h"

class CommentCommand : public Command
{
	const std::string syntax = "#";
public:
	CommentCommand();
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
};

