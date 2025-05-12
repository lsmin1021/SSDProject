#pragma once

#include "cmd_interface.h"
class HelpCmd : public CmdInterface {
public:
	HelpCmd() : CmdInterface("help", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() override;
};
