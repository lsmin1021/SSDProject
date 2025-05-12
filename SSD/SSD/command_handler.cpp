#include "cmd_checker.cpp"
#include "cmd_executor.cpp"


class CommandHandler {
public:
	CommandHandler() {
		m_executor = new CmdExecutor();
	}

	CommandHandler(CmdExecutor* executor) : m_executor(executor) { }

	void handleCommand(const vector<string>& cmdArr) {
		if (isValidCommand(cmdArr)) execute(cmdArr);
		else setError();
	}

	bool isValidCommand(const vector<string>& cmdArr) {
		if (m_checker.isEmptyCmd(cmdArr)) return false;
		if (m_checker.isValidWriteCommand(cmdArr)) return true;
		if (m_checker.isValidReadCommand(cmdArr)) return true;

		return false;
	}

	void execute(const vector<string>& cmd) {
		if (cmd[m_checker.COMMAND_INDEX] == m_checker.WRITE_COMMAND) {
			m_executor->write(std::stoi(cmd[m_checker.LBA_INDEX]), cmd[m_checker.VALUE_INDEX]);
		}
		else if (cmd[m_checker.COMMAND_INDEX] == m_checker.READ_COMMAND) {
			m_executor->read(std::stoi(cmd[m_checker.LBA_INDEX]));
		}
	}

	void setError() {
		m_executor->setError();
	}

private:
	CmdExecutor* m_executor = nullptr;
	CmdChecker m_checker;
};

