#include "command_write.h"
#include "buffer_handler.h"

WriteCommand::WriteCommand() {}

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

bool WriteCommand::isValidValue(const string& valueStr) {
	if (valueStr.length() != DATA_VALUE_LENGTH)
		return false;
	if (valueStr.find("0x") != 0)
		return false;

	for (char ch : valueStr.substr(2)) {
		if (!isxdigit(static_cast<unsigned char>(ch)))
			return false;
	}

	return true;
}

void WriteCommand::writeDataOnAddr(int lba, string value) {
	CommandBufferHandler& instance = CommandBufferHandler::getInstance();
	if (true == instance.isFull()) {
		instance.flush();
	}

	instance.writeBuffer(lba, value);
}