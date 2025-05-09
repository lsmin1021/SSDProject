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
		if (0 > lba || 100 <= lba) {
			throw std::exception("[WRITE ERROR] Out of lba");
		}
		m_ssdDevice[lba] = value;
	}

private:
	vector<string> m_ssdDevice;
};