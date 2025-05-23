#pragma once

#include "cmd_interface.h"

class FullWriteCmd : public CmdInterface {
public:
	FullWriteCmd() : CmdInterface("fullwrite", 2) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;
private :
	void fullWrite(const string& value);
};
