#pragma once
#include <map>
#include <memory>
#include <string>

#include "Interpeter/Stack.h"
#include "Interpeter/Commands/Command.h"

class LabelReferenceCommand : public Command
{
	const std::string syntax = ">";
public:
	LabelReferenceCommand(std::shared_ptr<Stack<std::string>> stack, std::shared_ptr<std::map<std::string, int>> labels);
	bool IsCommand(std::string& line) override;
	void Execute(std::string& line) override;
private:
	std::shared_ptr<Stack<std::string>> m_Stack;
	std::shared_ptr<std::map<std::string, int>> m_Labels;
};

