#pragma once

#include "cmd_interface.h"
class WriteCmd : public CmdInterface {
public:
	WriteCmd() : CmdInterface("write", 3) {}
	void checkInvalidCmd(const vector<string>& tokens) override {}
	void excuteCmd(const vector<string>& args) override {}
	void helpCmd() override {}
};
