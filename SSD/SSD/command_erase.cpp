#include "ICommand.h"
#include "output_handler.h"

EraseCommand::EraseCommand(NandHandler* nandHandler) : ICommand(nandHandler) {}

bool EraseCommand::isValid(const vector<string>& param) {
	if (PARAMETER_COUNT != param.size()) {
		return false;
	}
	else if (false == isValidLBA(param[LBA_INDEX])) {
		return false;
	}
	else if (false == isValidEraseNum(param[ERASE_CNT_INDEX])) {
		return false;
	}

	return true;
}

void EraseCommand::execute(const vector<string>& param) {
	int lba = std::stoi(param[LBA_INDEX]);
	int cnt = std::stoi(param[ERASE_CNT_INDEX]);

	eraseDataOnAddr(lba, cnt);
}

bool EraseCommand::isValidEraseNum(const string& eraseSizeStr) {
	// TODO:
	return true;
}

void EraseCommand::eraseDataOnAddr(int lba, int cnt) {
	return m_nandHandler->erase(lba, cnt);
}