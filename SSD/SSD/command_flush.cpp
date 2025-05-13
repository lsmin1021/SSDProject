#include "ICommand.h"

FlushCommand::FlushCommand(NandHandler* nandHandler) : ICommand(nandHandler) {}

bool FlushCommand::isValid(const vector<string>& param) {
	if (PARAMETER_COUNT != param.size()) {
		return false;
	}

	return true;
}

void FlushCommand::execute(const vector<string>& param) {
	flushBuffer();
}

void FlushCommand::flushBuffer() {
	// TODO
}