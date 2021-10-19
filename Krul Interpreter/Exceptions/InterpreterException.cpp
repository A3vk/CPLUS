#include "InterpreterException.h"

std::string InterpreterException::GetException() const
{
	return "InterpreterException: " + m_Msg;
}
