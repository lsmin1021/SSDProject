#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

class CommandHandler {
public:
	bool isValidCommand(vector<string> cmd) {
		if (cmd[0] == "W") {
			if (cmd.size() != 3) return false;
			if (std::stoi(cmd[1]) >= 100) return false;
				
		}

		return true;
	}
};
