#include "ICommand.h"

EraseCommand::EraseCommand(NandHandler* nandHandler) : ICommand(nandHandler) { }

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
	//m_nandHandler->erase(lba, size);
}

bool EraseCommand::isValidSize(const string& sizeStr) {
	try {
		size_t pos = 0;
		int size = std::stoi(sizeStr, &pos);
		if (pos != sizeStr.length())	return false;
		if (size < MIN_SIZE || size > MAX_SIZE) return false;
	}
	catch (std::invalid_argument&) {
		return false;
	}
	catch (std::out_of_range&) {
		return false;
	}

	return true;
}