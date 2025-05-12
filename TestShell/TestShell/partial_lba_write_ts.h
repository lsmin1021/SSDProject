#pragma once
#pragma once

#include "cmd_interface.h"
class PartialLbaWriteTs : public TsInterface {
public:
	PartialLbaWriteTs() : TsInterface("1_FullWriteAndReadCompare", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() override;
};
