#include "dll_main.h"
#include "testscript_interface.h"
#include "testscript_factory.h"

extern "C"{
    AppCb cb;
    
    LIB_API__ void openDll(AppCb* appCb) {
        cb = *appCb;
        TestScriptFactory::generateTs();
    }

    LIB_API__ void executeTs(const char* tsName) {
        std::string name = tsName;
        TsInterface* tsObj = TestScriptFactory::getInstance().getTs(name);
        vector<string> tokens;
        tokens.push_back(name);
        tsObj->excuteTs(tokens);
    }
}



