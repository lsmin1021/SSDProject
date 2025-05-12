#pragma once

#include "cmd_interface.h"
class FullWriteCmd : public CmdInterface {
public:
	FullWriteCmd() : CmdInterface("fullwrite", 2) {}
	void checkInvalidCmd(const vector<string>& tokens) override {}
	void excuteCmd(const vector<string>& args) override {}
	void helpCmd() override {}
};
