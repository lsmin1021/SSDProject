#pragma once

#include "cmd_interface.h"

class ExitCmd : public CmdInterface {
public :
	ExitCmd() : CmdInterface("exit", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;
};
