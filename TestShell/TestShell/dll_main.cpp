#include "dll_main.h"
#include "cmd_interface.h"
#include "cmd_factory.h"

static void executeTs_(const char* tsName)
{
    std::string name = tsName;
    CmdInterface* cmdObj = CmdFactory::getInstance().getTs(name);
    vector<string> tokens;
    tokens.push_back(tsName);
    cmdObj->excuteCmd(tokens);
}

extern "C" LIB_API__ void executeTs(const char* tsName)
{
    executeTs_(tsName);
}

