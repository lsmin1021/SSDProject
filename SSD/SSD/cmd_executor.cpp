
#include <iostream>

#include "nand_handler.cpp"

class CmdChecker {
public:
	static bool isValidLBA(int lba) {
		return isValidLBA(lba);
	}

	static bool isValidValue(string value) {
		if (false == isHexaFormat(value)) {
			return false;
		}
		else if (10 != value.length()) {
			return false;
		}
		else if (false == isHexaData(value.substr(2, 8))) {
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
	CmdExecutor() {}

	string read(int lba) {
		if (false == CmdChecker::isValidLBA(lba)) {
			throw std::exception("[READ ERROR] Out of lba");
		}

		string ssdDataStr = m_nandHandler.readNand();
		map<int, string> ssdData = m_nandHandler.getSSDData(ssdDataStr);
		if (ssdData.find(lba) == ssdData.end()) {
			return EMPTY_VALUE;
		}
		else {
			return ssdData[lba] ;
		}
	}

	void write(int lba, string value) {
		if (false == CmdChecker::isValidLBA(lba)) {
			throw std::exception("[WRITE ERROR] Out of lba");
		}
		if (false == CmdChecker::isValidValue(value)) {
			throw std::exception("[WRITE ERROR] Invalid value to write.");
		}

		string ssdDataStr = m_nandHandler.readNand();
		map<int, string> ssdData = m_nandHandler.getSSDData(ssdDataStr);

		if (ssdData.find(lba) == ssdData.end()) {
			ssdData.insert(std::make_pair(lba, value));
		}
		else {
			ssdData[lba] = value;
		}

		m_nandHandler.writeNand(ssdData);
	}

private:
	NandHandler m_nandHandler;
	const string EMPTY_VALUE = "0x00000000";
};
