#pragma once

#include "cmd_interface.h"
class ReadCmd : public CmdInterface {
public:
	ReadCmd() : CmdInterface("read", 2) {}
	void checkInvalidCmd(const vector<string>& tokens) override {}
	void excuteCmd(const vector<string>& args) override {}
	void helpCmd() override {}
};

