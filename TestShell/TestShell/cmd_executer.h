#pragma
#include <vector>
#include <string>

using std::vector;
using std::string;

class CmdExecuter {
public:
	static CmdExecuter& getInstance();
	static vector<string> converTokenCtoCpp(int numToken, char* tokens[]);
	bool executeCmd(const vector<string>& tokens);
private:

};