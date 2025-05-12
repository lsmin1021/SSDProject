#pragma once

#include <exception>
#include "cmd_interface.h"

class ExitException : public std::exception {
};

class ExitCmd : public CmdInterface {
public :
	ExitCmd() : CmdInterface("exit", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() override;
};
