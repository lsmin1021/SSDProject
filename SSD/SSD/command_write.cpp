#include "ICommand.h"

WriteCommand::WriteCommand(NandHandler* nandHandler) : ICommand(nandHandler) { }

bool WriteCommand::isValid(const vector<string>& param) {
	if (PARAMETER_COUNT != param.size()) {
		return false;
	}

	if (false == isValidLBA(param[LBA_INDEX])) {
		return false;
	}

	if (false == isValidValue(param[VALUE_INDEX])) {
		return false;
	}

	return true;
}

void WriteCommand::execute(const vector<string>& param) {
	writeDataOnAddr(std::stoi(param[LBA_INDEX]), param[VALUE_INDEX]);
}

void WriteCommand::writeDataOnAddr(int lba, string value) {
	m_nandHandler->write(lba, value);
}