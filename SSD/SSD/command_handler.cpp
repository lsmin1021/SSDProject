#include <iostream>
#include <string>
#include <vector>
#include "cmd_executor.cpp"

using std::vector;
using std::string;

class CommandHandler {
public:
	CommandHandler(CmdExecutor* app) : app(app) { }

	bool isValidCommand(vector<string> cmdArr) {
		if (isEmptyCmd(cmdArr)) return false;
		if (isValidWriteCommand(cmdArr)) return true;
		if (isValidReadCommand(cmdArr)) return true;

		return false;
	}

	void execute(const vector<string>& cmd) {
		if (cmd[COMMAND_INDEX] == WRITE_COMMAND) {
			app->write(std::stoi(cmd[LBA_INDEX]), cmd[VALUE_INDEX]);
		}
		if (cmd[COMMAND_INDEX] == READ_COMMAND) {
			app->read(std::stoi(cmd[LBA_INDEX]));
		}
	}
private:
	bool isEmptyCmd(const vector<string>& cmdArr) {
		return cmdArr.size() == 0;
	}

	bool isValidWriteCommand(const vector<string>& cmdArr) {
		if (cmdArr[COMMAND_INDEX] != WRITE_COMMAND) return false;
		if (cmdArr.size() != WRITE_ARGUMENT_COUNT) return false;
		if (isInvalidLBA(cmdArr[LBA_INDEX])) return false;
		if (isInvalidValue(cmdArr[VALUE_INDEX])) return false;
		return true;
	}

	bool isValidReadCommand(const vector<string>& cmdArr) {
		if (cmdArr[COMMAND_INDEX] != READ_COMMAND) return false;
		if (cmdArr.size() != READ_ARGUMENT_COUNT) return false;
		if (isInvalidLBA(cmdArr[LBA_INDEX])) return false;
		return true;
	}

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

	bool isInvalidValue(const string& valueString) {
		if (valueString.length() != LBA_STRING_LENGTH) return true;
		if (0 != valueString.find("0x")) return true;

		for (int i = 2; i < valueString.length(); i++) {
			if (isValidCharcter(valueString[i])) continue;
			return true;
		}
		return false;
	}

	bool isValidCharcter(char ch) {
		return ('0' <= ch && '9' >= ch) ||
			('a' <= ch && 'f' >= ch) ||
			('A' <= ch && 'F' >= ch);
	}

	CmdExecutor* app = nullptr;

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;
	const int LBA_STRING_LENGTH = 10;

	const string WRITE_COMMAND = "W";
	const string READ_COMMAND = "R";
	const int WRITE_ARGUMENT_COUNT = 3;
	const int READ_ARGUMENT_COUNT = 2;

	const int COMMAND_INDEX = 0;
	const int LBA_INDEX = 1;
	const int VALUE_INDEX = 2;
};
