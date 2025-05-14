#include "cmd_executer.h"
#include "cmd_interface.h"
#include "cmd_factory.h"
CmdExecuter& CmdExecuter::getInstance() {
	static CmdExecuter instance;
	return instance;
}
bool CmdExecuter::executeCmd(const vector<string>& tokens) {
    string cmdName = tokens[0];
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(cmdName);
    if (cmdObj == nullptr) return false;
    cmdObj->checkInvalidCmd(tokens);
    cmdObj->excuteCmd(tokens);
    return true;
}
vector<string> CmdExecuter::converTokenCtoCpp(int numToken, char* tokens[]) {
    vector<string> result;
    for (int index = 0; index < numToken; ++index){
        std::string cppStr = tokens[index];
        result.push_back(cppStr);
    }
    return result;
}

extern "C" bool executeCmd(int numToken, char* tokens[]) {
    return CmdExecuter::getInstance().executeCmd(CmdExecuter::converTokenCtoCpp(numToken, tokens));
}