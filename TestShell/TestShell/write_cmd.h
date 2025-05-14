#pragma once

#include "cmd_interface.h"

class WriteCmd : public CmdInterface {
public:
	WriteCmd() : CmdInterface("write", 3) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;
private :
	void write(const string& lba, const string& value);
};
