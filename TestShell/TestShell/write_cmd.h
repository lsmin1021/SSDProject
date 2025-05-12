#pragma once

#include "cmd_interface.h"
class WriteCmd : public CmdInterface {
public:
	WriteCmd() : CmdInterface("write", 3) {}
	void checkInvalidCmd(const vector<string>& tokens) override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() override;
private :
	void write(const string& lba, const string& value);
};
