#pragma once
#include "ICommand.h"

class WriteCommand : public ICommand {
public:
	WriteCommand(NandHandler* nandHandler);
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	void writeDataOnAddr(int lba, string value);
	bool isValidValue(const string& valueStr);

	const int PARAMETER_COUNT = 3;
	const int VALUE_INDEX = 2;
};