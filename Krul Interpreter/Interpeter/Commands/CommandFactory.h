#pragma once
class CommandFactory
{
public:
	~CommandFactory();

	static CommandFactory *Get()
	{
		static CommandFactory instance;
		return &instance;
	}

	void Register();
};

