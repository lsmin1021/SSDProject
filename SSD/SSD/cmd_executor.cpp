#include <vector>
#include <string>

using std::string;
using std::vector;

class CmdExecutor {
public:
	CmdExecutor() {
		for (int i = 0; i < 100; i++) {
			m_ssdDevice[i] = "";
		}
	}

	void write(int lba, string value) {
		m_ssdDevice[lba] = value;
	}

private:
	vector<string> m_ssdDevice;
};