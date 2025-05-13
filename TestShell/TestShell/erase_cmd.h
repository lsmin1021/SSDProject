#pragma once
#include "cmd_interface.h"
#include <vector>

using std::vector;

struct EraseArg {
	string lbaString;
	string sizeString;
};

class EraseCmd : public CmdInterface {
public:
	EraseCmd() : CmdInterface("erase", 3) {}
	EraseCmd(const string& name, int numToken) : CmdInterface(name, numToken) {}
	void checkInvalidCmd(const vector<string>& tokens) const override;
	void excuteCmd(const vector<string>& tokens) override;
	void helpCmd() const override;

private :
	static const int MAX_SIZE_FOR_SSD = 10;
	void checkSizeArg(const string& sizeSring) const;
	vector<EraseArg> makeFitSizeForSsd(const string& lba, const string& sizeSring);
};