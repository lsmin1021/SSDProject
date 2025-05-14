#include "command_erase.h"
#include "device_handler.h"

EraseCommand::EraseCommand() {}

bool EraseCommand::isValid(const vector<string>& param) {
	if (PARAMETER_COUNT != param.size()) {
		return false;
	}

	if (false == isValidLBA(param[LBA_INDEX])) {
		return false;
	}

	if (false == isValidSize(param[SIZE_INDEX])) {
		return false;
	}

	return true;
}

void EraseCommand::execute(const vector<string>& param) {
	eraseData(std::stoi(param[LBA_INDEX]), std::stoi(param[SIZE_INDEX]));
}

void EraseCommand::eraseData(int lba, int size) {
	DeviceHandler::getInstance().erase(lba, size);
}

bool EraseCommand::isValidSize(const string& sizeStr) {
	int size;
	if(toInt(sizeStr, size)) return (size >= MIN_SIZE && size <= MAX_SIZE);
	return false;
}