#include <iostream>
#include <string>
#include <vector>
#include "cmd_executor.cpp"

using std::vector;
using std::string;

class CommandHandler {
public:
	bool isValidCommand(vector<string> cmd) {
		if (cmd[0] == "W") {
			if (cmd.size() != 3) return false;

			try {
				size_t pos = 0;
				int a = std::stoi(cmd[1], &pos);
				if (a > 99 || a < 0) return false;
				if (pos != cmd[1].length())	return false;
			}
			catch (std::invalid_argument&) {
				return false;
			}
			catch (std::out_of_range&) {
				return false;
			}
			return true;
		}

		return false;
	}

	void execute(vector<string> cmd) {
		CmdExecutor app;
		if (cmd[0] == "W") {
			app.write(std::stoi(cmd[1]), cmd[2]);
		}
	}
};
