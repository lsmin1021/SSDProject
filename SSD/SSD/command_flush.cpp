#include "command_flush.h"
#include "buffer_handler.h"

FlushCommand::FlushCommand() {}

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
	CommandBufferHandler::getInstance().flush();
}