#pragma once
#include "ICommand.h"

class ReadCommand : public ICommand {
public:
	ReadCommand(NandHandler* nandHandler);
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	string readDataOnAddr(int lba);

	const int PARAMETER_COUNT = 2;
};