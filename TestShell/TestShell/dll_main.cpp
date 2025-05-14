#include "dll_main.h"
#include "testscript_interface.h"
#include "testscript_factory.h"

#include "stdio.h"
extern "C"{
    AppCb cb;
    
    LIB_API__ void openDll(AppCb* appCb) {
        printf("openDll %x %x\n", appCb, appCb->excueteCmd);
        cb = *appCb;
        TestScriptFactory::generateTs();
    }

    LIB_API__ void executeTs(const char* tsName) {
        printf("executeTs %s \n", tsName);
        std::string name = tsName;
        TsInterface* tsObj = TestScriptFactory::getInstance().getTs(name);
        printf("executeTs 1 %x \n", tsObj);
        vector<string> tokens;
        tokens.push_back(name);
        printf("executeTs 2\n");
        tsObj->excuteTs(tokens);
    }
}



