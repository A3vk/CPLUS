#include "CommentCommand.h"

CommentCommand::CommentCommand() = default;

bool CommentCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void CommentCommand::Execute(std::string& line) {}
