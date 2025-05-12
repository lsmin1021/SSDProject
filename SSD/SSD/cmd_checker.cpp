#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class CmdChecker {
public:
	bool isEmptyCmd(const vector<string>& cmdArr) {
		return cmdArr.size() == 0;
	}

	bool isValidWriteCommand(const vector<string>& cmdArr) {
		if (cmdArr[COMMAND_INDEX] != WRITE_COMMAND) return false;
		if (cmdArr.size() != WRITE_ARGUMENT_COUNT) return false;
		if (isInvalidLBA(cmdArr[LBA_INDEX])) return false;
		if (isInvalidDataValue(cmdArr[VALUE_INDEX])) return false;
		return true;
	}

	bool isValidReadCommand(const vector<string>& cmdArr) {
		if (cmdArr[COMMAND_INDEX] != READ_COMMAND) return false;
		if (cmdArr.size() != READ_ARGUMENT_COUNT) return false;
		if (isInvalidLBA(cmdArr[LBA_INDEX])) return false;
		return true;
	}
private:
	bool isInvalidLBA(const string& lbaString) {
		try {
			size_t pos = 0;
			int lba = std::stoi(lbaString, &pos);
			if (pos != lbaString.length())	return true;
			if (lba < MIN_LBA || lba > MAX_LBA) return true;
		}
		catch (std::invalid_argument&) {
			return true;
		}
		catch (std::out_of_range&) {
			return true;
		}
		return false;
	}

	bool isInvalidDataValue(const string& valueString) {
		if (valueString.length() != DATA_VALUE_LENGTH) return true;
		if (valueString.find("0x") != 0) return true;

		for (char ch : valueString.substr(2)) {
			if (!isxdigit(static_cast<unsigned char>(ch))) return true;
		}
		return false;
	}

public:
	const string WRITE_COMMAND = "W";
	const string READ_COMMAND = "R";

	const int WRITE_ARGUMENT_COUNT = 3;
	const int READ_ARGUMENT_COUNT = 2;

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;
	const int DATA_VALUE_LENGTH = 10;

	const int COMMAND_INDEX = 0;
	const int LBA_INDEX = 1;
	const int VALUE_INDEX = 2;
};
