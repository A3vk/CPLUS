#include "EndCommand.h"

EndCommand::EndCommand(bool* reachedEnd) : m_reachedEnd(reachedEnd) {}

bool EndCommand::IsCommand(std::string& line)
{
	return line.rfind(syntax, 0) != std::string::npos;
}

void EndCommand::Execute(std::string& line)
{
	*m_reachedEnd = true;
}