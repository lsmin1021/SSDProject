#include "command_read.h"
#include "nand_handler.h"
#include "output_handler.h"
#include "buffer_handler.h"

ReadCommand::ReadCommand() {}

bool ReadCommand::isValid(const vector<string>& param) {
	if (PARAMETER_COUNT != param.size()) {
		return false;
	}

	return isValidLBA(param[LBA_INDEX]);
}

void ReadCommand::execute(const vector<string>& param) {
	int lba = std::stoi(param[LBA_INDEX]);

	string ret = CommandBufferHandler::getInstance().readBuffer(lba);
	
	if (true == ret.empty()) {
		ret = readDataOnAddr(lba);
	}

	OutputHandler::getInstance().write(ret);
}

string ReadCommand::readDataOnAddr(int lba) {
	return NandHandler::getInstance().read(lba);
}