#include "cmd_executer.h"
#include "cmd_interface.h"
#include "cmd_factory.h"
#include "logger.h"

CmdExecuter& CmdExecuter::getInstance() {
	static CmdExecuter instance;
	return instance;
}
CmdInterface* CmdExecuter::executeCmd(const vector<string>& tokens) {
    string cmdName = tokens[0];
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(cmdName);
    if (cmdObj == nullptr) return nullptr;
    cmdObj->checkInvalidCmd(tokens);

    LOG_PRINT("CmdExecuter", "Execute " + cmdName + "\n");
    cmdObj->excuteCmd(tokens);
    return cmdObj;
}

static const string NOT_CHECK_RESULT = "NOT_CHECK_RESULT";
extern "C" bool executeCmdCb(const vector<string>& cmdTokens, const string& checkString) {
    LOG_PRINT("CmdExecuter", "Execute " + cmdTokens[0] + " from testScript" + "\n");
    CmdInterface* cmdObj =  CmdExecuter::getInstance().executeCmd(cmdTokens);
    if (cmdObj == nullptr) return false;

    if (checkString == NOT_CHECK_RESULT) return true;
   
    if (cmdObj->getReadResult() != checkString) {
        throw FailException();
    }
    return true;
}