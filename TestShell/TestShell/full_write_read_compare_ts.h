#pragma once
#include <iostream>
#include "testscript_interface.h"

class FullWriteAndReadCompareTs : public TsInterface {
public:
	FullWriteAndReadCompareTs(AppCb* appCb) : TsInterface("1_FullWriteAndReadCompare", 1, appCb) {}
	void checkInvalidTs(const vector<string>& tokens) const override;
	void excuteTs(const vector<string>& tokens) override;

private:
	static const int TEST_LBA_STEP = 5;
	const string TEST_SCRIPT_VALUE = "0x5A5A5A5A";
};
