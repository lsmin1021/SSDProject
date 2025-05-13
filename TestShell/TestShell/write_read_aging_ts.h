#pragma once
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include "cmd_interface.h"
class WriteReadAging : public TsInterface {
public:
	WriteReadAging() : TsInterface("3_WriteReadAging", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
private:
	static const int TEST_MAX_ITERATE = 200;
	const string TEST_SCRIPT_VALUE = "0x5A5A5A5A";
	const string START_LBA = "0";
	const string END_LBA = "99";
	string generateRandomHexString();
};
#pragma once
