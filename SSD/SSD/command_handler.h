#pragma once
#include "ICommand.h"

class CommandFactory {
public:
	static std::unique_ptr<ICommand> makeCommand(const string& cmd);
};

class CommandHandler {
public:
	CommandHandler();

	bool handleCommand(const vector<string>& cmdArr);

private:
	bool isValidCommand(const vector<string>& cmdArr);
	void executeCommand(const vector<string>& cmdArr);

	std::unique_ptr<ICommand> m_command;
};
