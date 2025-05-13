#pragma once

#include "erase_cmd.h"

class EraseRangeCmd : public EraseCmd {
public:
	EraseRangeCmd() : EraseCmd("erase_range", 3) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;
};