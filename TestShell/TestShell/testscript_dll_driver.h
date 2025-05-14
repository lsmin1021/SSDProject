#pragma once
#include <iostream>
#include <windows.h>

class TsDllDriver {
public:
    TsDllDriver();

    ~TsDllDriver() {
        FreeLibrary(m_dll);
    }

    static TsDllDriver& getInstance();


private:
    HMODULE m_dll;
};