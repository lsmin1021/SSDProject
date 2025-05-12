#pragma once

#include "cmd_interface.h"
class ReadCmd : public CmdInterface {
public:
	ReadCmd() : CmdInterface("read", 2) {}
	void checkInvalidCmd(const vector<string>& tokens) override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() override;
private :
	void read(const string& lbaString);
};

