#pragma
#include <vector>
#include <string>

using std::vector;
using std::string;
class CmdInterface;
class CmdExecuter {
public:
	static CmdExecuter& getInstance();
	CmdInterface* executeCmd(const vector<string>& tokens);
private:
};