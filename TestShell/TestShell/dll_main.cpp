#include "dll_main.h"
#include "testscript_factory.h"

static void executeTs_(const char* tsName)
{
    std::string name = tsName;
    TsInterface* cmdObj = TestScriptFactory::getInstance().getCmd(name);
    vector<string> tokens;
    tokens.push_back(tsName);
    // LDY TODO
    //cmdObj->excuteCmd(tokens);
}
extern "C"{
    LIB_API__ void executeTs(const char* tsName)
    {
        executeTs_(tsName);
    }
    AppCb appCb;
}



