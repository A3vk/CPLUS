#pragma once
#include <exception>
#include <string>

class InterpreterException : public std::exception
{
public:
	InterpreterException(const std::string& url) : exception(url.c_str()), m_Msg(url) {}
	std::string GetException() const;
private:
	std::string m_Msg;
};

