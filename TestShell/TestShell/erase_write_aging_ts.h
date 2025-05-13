#pragma once
#include <iostream>
#include "cmd_interface.h"

class EraseAndWriteAgingTs : public TsInterface {
public:
	EraseAndWriteAgingTs() : TsInterface("4_EraseAndWriteAging", 1) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
private:
	const int TEST_MAX_ITERATE = 30;
	const int TEST_ERASE_SIZE_INT = 3;
	const string TEST_ERASE_SIZE = "3";
	const string TEST_SCRIPT_VALUE = "0x5A5A5A5A";
	const string TEST_SCRIPT_OVERWRITE_VALUE = "0xA5A5A5A5";
	const string TEST_EXPECTED_VALUE = "0x00000000";
	int nextLbaAddr(int lba) const;
	void eraseAndReadAssert(const string& addr) const;
	void readAndCompare(const string& addr) const;
	void writeAndErase(const string& addr) const;
};
