#include <iostream>
#include <string>
#include <vector>
#include "cmd_executor.cpp"

using std::vector;
using std::string;

class CommandHandler {
private:
	const int MAX_LBA = 99;
	const int MIN_LBA = 0;
public:
	bool isValidCommand(vector<string> cmdArr) {
		if (isEmptyCmd(cmdArr)) return false;
		if (isValidWriteCommand(cmdArr)) {
			if (isValidLBA(cmdArr) == false) return false;
			return true;
		}

		return false;
	}

	bool isValidWriteCommand(vector<string>& cmd) {
		return cmd[0] == "W" && cmd.size() == 3;
	}

	bool isEmptyCmd(vector<string>& cmd) {
		return cmd.size() == 0;
	}

	bool isValidLBA(vector<string>& cmdArr) {
		try {
			size_t pos = 0;
			int lba = std::stoi(cmdArr[1], &pos);
			if (pos != cmdArr[1].length())	return false;
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

	void execute(vector<string> cmd) {
		CmdExecutor app;
		if (cmd[0] == "W") {
			app.write(std::stoi(cmd[1]), cmd[2]);
		}
	}
};
