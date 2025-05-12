#pragma once
#pragma once
#include <iostream>
#include "cmd_interface.h"
#include "ssd_interface.h"

class PartialLbaWriteTs : public TsInterface {
public:
	PartialLbaWriteTs() : TsInterface("2_PartialLBAWrite", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() override;
private:
	static const int MAX_LBA = 99;
	static const int TEST_SCRIPT2_REPEAT_NUM = 30;
	static const int TEST_SCRIPT2_LBA_STEP = 5;
	const string TEST_SCRIPT_VALUE = "0x5A5A5A5A";
};
