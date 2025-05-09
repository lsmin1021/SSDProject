#include <vector>
#include <string>

#include "nand_handler.cpp"

using std::string;
using std::vector;

class CmdExecutor {
public:
	CmdExecutor() {
		for (int i = 0; i < 100; i++) {
			m_ssdDevice.push_back("");
		}
	}

	string read(int lba) {
		if (false == isValidLBA(lba)) {
			throw std::exception("[READ ERROR] Out of lba");
		}

		if (true == isEmptyLBA(lba)) {
			return EMPTY_VALUE;
		}

		return m_ssdDevice[lba];
	}

	void write(int lba, string value) {
		if (false == isValidLBA(lba)) {
			throw std::exception("[WRITE ERROR] Out of lba");
		}
		if (false == isValidValue(value)) {
			throw std::exception("[WRITE ERROR] Invalid value to write.");
		}

		m_ssdDevice[lba] = value;

		string ret;
		for (int i = 0; i < m_ssdDevice.size(); i++) {
			ret.append(std::to_string(i));
			ret.append(" ");
			ret.append(m_ssdDevice[i]);
			ret.append("\n");
		}
		m_nandHandler->write(ret);
	}

	void setNandHandler(FileHandler* handler) {
		m_nandHandler = handler;
	}

	void setOutputHandler(FileHandler* handler) {
		m_outputHandler = handler;
	}

private:
	bool isEmptyLBA(int lba) {
		if (true == m_ssdDevice[lba].empty()) {
			return true;
		}

		return false;
	}

	bool isValidLBA(int lba) {
		if (0 > lba || 100 <= lba) {
			return false;
		}

		return true;
	}

	bool isValidValue(string value) {
		if (0 != value.find("0x")) {
			return false;
		}
		else if (10 != value.length()) {
			return false;
		}
		else {
			for (int i = 0; i < value.length(); i++) {
				if (('0' <= value[i] && '9' >= value[i]) ||
					('a' <= value[i] && 'z' >= value[i]) ||
					('A' <= value[i] && 'Z' >= value[i])) {
					continue;
				}

				return false;
			}
		}

		return true;
	}

	vector<string> m_ssdDevice;

	FileHandler* m_nandHandler = nullptr;
	FileHandler* m_outputHandler = nullptr;

	const string EMPTY_VALUE = "0x00000000";


};