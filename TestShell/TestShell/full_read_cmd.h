#pragma once

#include "cmd_interface.h"

class FullReadCmd : public CmdInterface {
public:
	FullReadCmd() : CmdInterface("fullread", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;
private :
	void fullRead();
};

