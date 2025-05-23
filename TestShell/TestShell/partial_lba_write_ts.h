#pragma once
#pragma once
#include <iostream>
#include "testscript_interface.h"

class PartialLbaWriteTs : public TsInterface {
public:
	PartialLbaWriteTs(AppCb* appCb) : TsInterface("2_PartialLBAWrite", 1, appCb) {}
	void checkInvalidTs(const vector<string>& tokens) const override;
	void excuteTs(const vector<string>& tokens) override;
private:
	static const int TEST_SCRIPT2_REPEAT_NUM = 30;
	static const int TEST_SCRIPT2_LBA_STEP = 5;
	const string TEST_SCRIPT_VALUE = "0x5A5A5A5A";
};
