#include "cmd_executer.h"
#include "cmd_interface.h"
#include "cmd_factory.h"
#include <iostream>
CmdExecuter& CmdExecuter::getInstance() {
	static CmdExecuter instance;
	return instance;
}
CmdInterface* CmdExecuter::executeCmd(const vector<string>& tokens) {
    string cmdName = tokens[0];
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(cmdName);
    if (cmdObj == nullptr) return nullptr;
    cmdObj->checkInvalidCmd(tokens);
    cmdObj->excuteCmd(tokens);
    return cmdObj;
}
vector<string> CmdExecuter::converTokenCtoCpp(int numToken, char tokens[10][100]) {
    vector<string> result;
    for (int index = 0; index < numToken; ++index){
        std::string cppStr = tokens[index];
        result.push_back(cppStr);
    }
    return result;
}
const char* NOT_CHECK_RESULT = "NOT_CHECK_RESULT";
extern "C" bool executeCmd(int numToken, char tokens[10][100], const char checkString[100]) {
    CmdInterface* cmdObj =  CmdExecuter::getInstance().executeCmd(CmdExecuter::converTokenCtoCpp(numToken, tokens));
    if (cmdObj == nullptr) return false;

    //std::cout << "executeCmd : " << checkString << "\n";
    int result = std::strcmp(checkString, NOT_CHECK_RESULT);
    if (result) {
        string mustString = checkString;
        if (cmdObj->getReadResult() != mustString) {
            throw FailException();
        }
    }
    return true;
}