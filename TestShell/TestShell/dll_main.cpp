#include "dll_main.h"
#include "testscript_interface.h"
#include "testscript_factory.h"

extern "C"{
    AppCb cb;
    
    LIB_API__ void openDll(AppCb* appCb) {
        cb = *appCb;
        TestScriptFactory::generateTs();
    }

    LIB_API__ void executeTs(const vector<string>& cmdTokens) {
        std::string name = cmdTokens[0];
        TsInterface* tsObj = TestScriptFactory::getInstance().getTs(name);
        tsObj->excuteTs(cmdTokens);
    }
}



