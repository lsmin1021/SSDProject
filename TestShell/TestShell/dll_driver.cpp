#include "dll_driver.h"
#include "dll_main.h"


DllDriver& DllDriver::getInstance()
{
    static DllDriver instance;
    return instance;
}

void DllDriver::openTestShellLib() {
    HMODULE m_dll = LoadLibraryA("TestShellLib.dll");
    if (m_dll == nullptr) {
        std::cerr << "DLL load fail!" << std::endl;
        return;
    }
    m_dllApi.openDll = (OpenDll)GetProcAddress(m_dll, "openDll");
    if (m_dllApi.openDll)  m_dllApi.openDll();
    else {
        std::cerr << "openDll symbol search fali!" << std::endl;
        FreeLibrary(m_dll);
        return; 
    }

    m_dllApi.executeTs = (ExecuteTs)GetProcAddress(m_dll, "executeTs");
    if (m_dllApi.executeTs == nullptr) {
        std::cerr << "executeTs symbol search fali!" << std::endl;
    }
}