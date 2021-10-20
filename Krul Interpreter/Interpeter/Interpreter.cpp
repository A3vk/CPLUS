#include "Interpreter.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "Commands/FunctionCommands/FunctionDefinitionCommand.h"
#include "Commands/FunctionCommands/FunctionReturnCommand.h"
#include "Commands/IntegerCommands/AbsoluteCommand.h"
#include "Commands/IntegerCommands/AddCommand.h"
#include "Commands/IntegerCommands/DecrementCommand.h"
#include "Commands/IntegerCommands/DivideCommand.h"
#include "Commands/IntegerCommands/IncrementCommand.h"
#include "Commands/IntegerCommands/ModuloCommand.h"
#include "Commands/IntegerCommands/MultiplyCommand.h"
#include "Commands/IntegerCommands/NegateCommand.h"
#include "Commands/IntegerCommands/SubtractCommand.h"
#include "Commands/OtherCommands/CommentCommand.h"
#include "Commands/OtherCommands/EndCommand.h"
#include "Commands/StringCommands/ConcatenationCommand.h"
#include "Commands/StringCommands/DuplicateCommand.h"
#include "Commands/StringCommands/IndexCommand.h"
#include "Commands/StringCommands/LengthCommand.h"
#include "Commands/StringCommands/NewLineCommand.h"
#include "Commands/StringCommands/ReverseCommand.h"
#include "Commands/StringCommands/RotateCommand.h"
#include "Commands/StringCommands/SubstringCommand.h"
#include "Commands/TestJumpCommands/GotoCommand.h"
#include "Commands/TestJumpCommands/GotoIfEqualCommand.h"
#include "Commands/TestJumpCommands/GotoIfGreaterCommand.h"
#include "Commands/TestJumpCommands/GotoIfGreaterOrEqualCommand.h"
#include "Commands/TestJumpCommands/GotoIfLessCommand.h"
#include "Commands/TestJumpCommands/GotoIfLessOrEqualCommand.h"
#include "Commands/TestJumpCommands/GotoIfNotEqualCommand.h"
#include "Commands/ValueTypeCommands/IntegerCommand.h"
#include "Commands/ValueTypeCommands/LabelDefinitionCommand.h"
#include "Commands/ValueTypeCommands/LabelReferenceCommand.h"
#include "Commands/ValueTypeCommands/StringCommand.h"
#include "Commands/ValueTypeCommands/VariableAssignmentCommand.h"
#include "Commands/ValueTypeCommands/VariableReferenceCommand.h"
#include "Exceptions/InterpreterException.h"

Interpreter::Interpreter()
{
	stack = std::make_shared<Stack<std::string>>();
	callStack = std::make_shared<Stack<int>>();
	variables = std::make_shared<std::map<std::string, std::string>>();
	labels = std::make_shared<std::map<std::string, int>>();

	//m_Factory = CommandFactory::Get();
	m_Factory = CommandFactory::GetInstance();
	RegisterCommands();
}

std::shared_ptr<InterpreterResult> Interpreter::Interpret(const std::string& file)
{
	const std::vector<std::string> lines = SplitLines(file);
	reachedEnd = false;
	
	// Get all reference assignments
	for (size_t index = 0; index < lines.size(); index++)
	{
		const std::string line = lines[index];
		if (line.rfind(':', 0) != std::string::npos)
		{
			labels->insert_or_assign(line.substr(1), index);
		}
	}

	for (lineNumber = 0; lineNumber < lines.size(); lineNumber++)
	{
		std::string currentLine = lines[lineNumber];

		try
		{
			m_Factory->Create(currentLine)->Execute(currentLine);
		}
		catch (InterpreterException e)
		{
			std::cout << e.GetException() << std::endl;
			return std::make_shared<InterpreterResult>("", true);
		}

		if (reachedEnd) 
			break;
	}

	auto result = stack->back();
	CleanUp();
	return std::make_shared<InterpreterResult>(result, reachedEnd);
}

void Interpreter::RegisterCommands()
{
	// Values and Types
	m_Factory->Register<IntegerCommand>(stack);
	m_Factory->Register<StringCommand>(stack);
	m_Factory->Register<LabelDefinitionCommand>();
	m_Factory->Register<LabelReferenceCommand>(stack, labels);
	m_Factory->Register<VariableAssignmentCommand>(stack, variables);
	m_Factory->Register<VariableReferenceCommand>(stack, variables);
	// IntegerCommand
	m_Factory->Register<AbsoluteCommand>(stack);
	m_Factory->Register<AddCommand>(stack);
	m_Factory->Register<DecrementCommand>(stack);
	m_Factory->Register<DivideCommand>(stack);
	m_Factory->Register<IncrementCommand>(stack);
	m_Factory->Register<ModuloCommand>(stack);
	m_Factory->Register<MultiplyCommand>(stack);
	m_Factory->Register<NegateCommand>(stack);
	m_Factory->Register<SubtractCommand>(stack);
	// StringCommand
	m_Factory->Register<ConcatenationCommand>(stack);
	m_Factory->Register<DuplicateCommand>(stack);
	m_Factory->Register<IndexCommand>(stack);
	m_Factory->Register<LengthCommand>(stack);
	m_Factory->Register<NewLineCommand>(stack);
	m_Factory->Register<ReverseCommand>(stack);
	m_Factory->Register<RotateCommand>(stack);
	m_Factory->Register<SubstringCommand>(stack);
	// Test and Jump
	m_Factory->Register<GotoCommand>(stack, &lineNumber);
	m_Factory->Register<GotoIfEqualCommand>(stack, &lineNumber);
	m_Factory->Register<GotoIfGreaterCommand>(stack, &lineNumber);
	m_Factory->Register<GotoIfGreaterOrEqualCommand>(stack, &lineNumber);
	m_Factory->Register<GotoIfLessCommand>(stack, &lineNumber);
	m_Factory->Register<GotoIfLessOrEqualCommand>(stack, &lineNumber);
	m_Factory->Register<GotoIfNotEqualCommand>(stack, &lineNumber);
	// Functions
	m_Factory->Register<FunctionDefinitionCommand>(stack, callStack, &lineNumber);
	m_Factory->Register<FunctionReturnCommand>(callStack, &lineNumber);
	// Other
	m_Factory->Register<CommentCommand>();
	m_Factory->Register<EndCommand>(&reachedEnd);
}

std::vector<std::string> Interpreter::SplitLines(const std::string& input) const
{
	std::vector<std::string> lines;
	std::stringstream stream(input);
	std::string line;

	while(std::getline(stream, line, '\n'))
	{
		lines.push_back(line);
	}

	return lines;
}

void Interpreter::CleanUp() const
{
	stack->clear();
	callStack->clear();
	variables->clear();
	labels->clear();
}
