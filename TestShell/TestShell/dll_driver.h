#pragma once
#include <iostream>
#include <windows.h>

#include "dll_main.h"

struct DllApi {
    OpenDll openDll;
    ExecuteTs executeTs;
};

class DllDriver {
public:
    DllDriver() = default;
   
    ~DllDriver() {
        FreeLibrary(m_dll);
    }

    static DllDriver& getInstance();
    void openDll() {
        openTestShellLib();
    }

    DllApi& getDllApi() {
       return m_dllApi;
    }
private:
    void openTestShellLib();

    HMODULE m_dll;
    DllApi m_dllApi;
    
 
};
