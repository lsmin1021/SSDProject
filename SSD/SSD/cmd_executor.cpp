
#include <iostream>

#include "output_handler.cpp"
#include "nand_handler.cpp"

class CmdChecker {
public:
	static bool isValidLBA(int lba) {
		return isValidRange(lba);
	}

	static bool isValidValue(string value) {
		if (false == isHexaFormat(value)) {
			return false;
		}
		else if (10 != value.length()) {
			return false;
		}
		else if (false == isHexaData(value.substr(2))) {
			return false;
		}

		return true;
	}

private:
	static bool isValidRange(int lba) {
		if (0 > lba || 100 <= lba) {
			return false;
		}

		return true;
	}

	static bool isHexaFormat(string value) {
		if (0 != value.find("0x")) {
			return false;
		}

		return true;
	}

	static bool isHexaData(string value) {
		for (int i = 0; i < value.length(); i++) {
			if (('0' <= value[i] && '9' >= value[i]) ||
				('a' <= value[i] && 'f' >= value[i]) ||
				('A' <= value[i] && 'F' >= value[i])) {
				continue;
			}

			return false;
		}

		return true;
	}
};

class CmdExecutor {
public:
	CmdExecutor() {
		m_nandHandler = new NandHandler();
		m_outputHandler = new OutputHandler();
	}

	string read(int lba) {
		if (false == CmdChecker::isValidLBA(lba)) {
			throw std::out_of_range("[READ ERROR] Out of lba");
		}

		string ret = readDataOnAddr(lba);

		m_outputHandler->write(ret);

		return ret;
	}

	void write(int lba, string value) {
		if (false == CmdChecker::isValidLBA(lba)) {
			throw std::out_of_range("[WRITE ERROR] Out of lba");
		}
		if (false == CmdChecker::isValidValue(value)) {
			throw std::invalid_argument("[WRITE ERROR] Invalid value to write.");
		}

		writeDataOnAddr(lba, value);
	}

	void setError() {
		m_outputHandler->write("ERROR");
	}
	
	void setNandHandler(NandInterface* handler) {
		m_nandHandler = handler;
	}

	void setOutputHandler(OutputInterface* handler) {
		m_outputHandler = handler;
	}

private:
	string readDataOnAddr(int lba) {
		m_nandHandler->read();

		return m_nandHandler->getData(lba);
	}

	void writeDataOnAddr(int lba, string value) {
		m_nandHandler->read();

		m_nandHandler->write(lba, value);
	}

	NandInterface* m_nandHandler;
	OutputInterface* m_outputHandler;
};
