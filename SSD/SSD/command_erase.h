#pragma once
#include "ICommand.h"

class EraseCommand : public ICommand {
public:
	EraseCommand(NandHandler* nandHandler);
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	void eraseData(int lba, int size);
	bool isValidSize(const string& valueStr);

	const int PARAMETER_COUNT = 3;
	const int SIZE_INDEX = 2;

	const int MAX_SIZE = 10;
	const int MIN_SIZE = 0;
};