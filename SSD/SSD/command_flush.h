#pragma once
#include "ICommand.h"

class FlushCommand : public ICommand {
public:
	FlushCommand();
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	void flushBuffer();

	const int PARAMETER_COUNT = 1;
};
