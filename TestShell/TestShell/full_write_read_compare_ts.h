#pragma once
#include <iostream>
#include "cmd_interface.h"
#include "ssd_interface.h"

class FullWriteAndReadCompareTs : public TsInterface {
public:
	FullWriteAndReadCompareTs() : TsInterface("1_FullWriteAndReadCompare", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
private:
	static const int TEST_LBA_STEP = 5;
	const string TEST_SCRIPT_VALUE = "0x5A5A5A5A";
};
