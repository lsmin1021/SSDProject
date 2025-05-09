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
			if (isValidLBA(cmdArr[1]) == false) return false;
			if (isValidValue(cmdArr[2]) == false) return false;

			return true;
		}

		return false;
	}

	void execute(const vector<string>& cmd) {
		CmdExecutor app;
		if (cmd[0] == "W") {
			app.write(std::stoi(cmd[1]), cmd[2]);
		}
	}
private:
	bool isValidValue(const string& value) {
		if (value.length() != 10) return false;
		if (0 != value.find("0x")) return false;

		for (int i = 2; i < value.length(); i++) {
			char ch = value[i];
			if (('0' <= ch && '9' >= ch) ||
				('a' <= ch && 'f' >= ch) ||
				('A' <= ch && 'F' >= ch)) {
				continue;
			}
			return false;
		}
		return true;
	}

	bool isValidWriteCommand(const vector<string>& cmd) {
		return cmd[0] == "W" && cmd.size() == 3;
	}

	bool isEmptyCmd(const vector<string>& cmd) {
		return cmd.size() == 0;
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

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;
};
