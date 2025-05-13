#pragma once

#include "cmd_interface.h"

class EraseRangeCmd : public CmdInterface {
public:
	EraseRangeCmd() : CmdInterface("erase", 3) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;
};