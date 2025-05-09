#include <vector>
#include <string>

using std::string;
using std::vector;

class CmdExecutor {
public:
	CmdExecutor() {
		for (int i = 0; i < 100; i++) {
			m_ssdDevice.push_back("");
		}
	}

	void write(int lba, string value) {
		if (false == isValidLBA(lba)) {
			throw std::exception("[WRITE ERROR] Out of lba");
		}
		if (false == isValidValue(value)) {
			throw std::exception("[WRITE ERROR] Invalid value to write.");
		}

		m_ssdDevice[lba] = value;
	}

private:
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
};