#pragma once

#include "cmd_interface.h"
class WriteReadAging : public TsInterface {
public:
	WriteReadAging() : TsInterface("3_WriteReadAging", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() override;
};
#pragma once
