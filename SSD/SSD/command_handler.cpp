#include <iostream>
#include <string>
#include <vector>
#include "cmd_executor.cpp"

using std::vector;
using std::string;

class CommandHandler {
public:
	bool isValidCommand(vector<string> cmdArr) {
		if (isEmptyCmd(cmdArr)) return false;
		if (isValidWriteCommand(cmdArr)) {
			if (isValidLBA(cmdArr[LBA_INDEX]) == false) return false;
			if (isValidValue(cmdArr[VALUE_INDEX]) == false) return false;
			return true;
		}
		if (cmdArr[0] == "R") {
			if (cmdArr.size() != 2) return false;
			
			return true;
		}

		return false;
	}

	void execute(const vector<string>& cmd) {
		CmdExecutor app;
		if (cmd[COMMAND_INDEX] == "W") {
			app.write(std::stoi(cmd[LBA_INDEX]), cmd[VALUE_INDEX]);
		}
	}
private:
	bool isEmptyCmd(const vector<string>& cmdArr) {
		return cmdArr.size() == 0;
	}

	bool isValidWriteCommand(const vector<string>& cmdArr) {
		return (cmdArr[COMMAND_INDEX] == WRITE_COMMAND && cmdArr.size() == WRITE_ARGUMENT_COUNT);
	}

	bool isValidLBA(const string& lbaString) {
		try {
			size_t pos = 0;
			int lba = std::stoi(lbaString, &pos);
			if (pos != lbaString.length())	return false;
			if (lba < MIN_LBA || lba > MAX_LBA) return false;
		}
		catch (std::invalid_argument&) {
			return false;
		}
		catch (std::out_of_range&) {
			return false;
		}
		return true;
	}

	bool isValidValue(const string& valueString) {
		if (valueString.length() != 10) return false;
		if (0 != valueString.find("0x")) return false;

		for (int i = 2; i < valueString.length(); i++) {
			if (isValidCharcter(valueString[i])) continue;
			return false;
		}
		return true;
	}

	bool isValidCharcter(char ch) {
		return ('0' <= ch && '9' >= ch) ||
			('a' <= ch && 'f' >= ch) ||
			('A' <= ch && 'F' >= ch);
	}

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;

	const string WRITE_COMMAND = "W";
	const int WRITE_ARGUMENT_COUNT = 3;

	const int COMMAND_INDEX = 0;
	const int LBA_INDEX = 1;
	const int VALUE_INDEX = 2;
};
