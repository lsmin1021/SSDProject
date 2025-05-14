#include "testscript_dll_driver.h"
#include "ts1dll.h"
#include "testscript_factory.h"

TsDllDriver::TsDllDriver() {
    HMODULE m_dll = LoadLibraryA("Ts1Dll.dll");
    if (m_dll == nullptr) {
        std::cerr << "TsDllDriver load fail!" << std::endl;
        return;
    }
    GetInstance getInstance = (GetInstance)GetProcAddress(m_dll, "getInstance");
    TestScriptFactory::getInstance().registerTs(getInstance(&cb));
}

TsDllDriver& TsDllDriver::getInstance()
{
    static TsDllDriver instance;
    return instance;
}