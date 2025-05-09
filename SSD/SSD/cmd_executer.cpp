#include <vector>
#include <string>

using std::string;
using std::vector;

class CmdExecuter {
public:
	CmdExecuter() {

	}

	void write(int lba, string value) {
		m_ssdDevice[lba] = value;
	}
private:
	vector<string> m_ssdDevice;
};