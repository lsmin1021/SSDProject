#pragma
#include <vector>
#include <string>

using std::vector;
using std::string;
class CmdInterface;
class CmdExecuter {
public:
	static CmdExecuter& getInstance();
	static vector<string> converTokenCtoCpp(int numToken, char tokens[10][100]);
	CmdInterface* executeCmd(const vector<string>& tokens);
private:
};