#pragma once

#include "cmd_interface.h"

class FlushCmd : public CmdInterface {
public:
	FlushCmd() : CmdInterface("flush", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;
};