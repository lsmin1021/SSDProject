#include "ICommand.h"
#include "output_handler.h"

ReadCommand::ReadCommand(NandHandler* nandHandler) : ICommand(nandHandler) { }

bool ReadCommand::isValid(const vector<string>& param) {
	if (PARAMETER_COUNT != param.size()) {
		return false;
	}

	return isValidLBA(param[LBA_INDEX]);
}

void ReadCommand::execute(const vector<string>& param) {
	int lba = std::stoi(param[LBA_INDEX]);
	string ret = readDataOnAddr(lba);

	OutputHandler::getInstance().write(ret);
}

string ReadCommand::readDataOnAddr(int lba) {
	return m_nandHandler->read(lba);
}