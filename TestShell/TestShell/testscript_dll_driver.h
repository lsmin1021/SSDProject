#pragma once
#include <iostream>
#include <windows.h>
#include "dll.h"

using std::wstring;

class TsDllDriver {
public:
    TsDllDriver(AppCb* appCb);

    ~TsDllDriver() {
        FreeLibrary(m_dll);
    }

    static TsDllDriver& getInstance(AppCb* appCb);

private:
    vector<string>  getDllFileNames(const string& folderPath);
    void openTestShellLib(AppCb* appCb, string dllFileName);
    GetInstance getInstanceApi(string flleName);
    HMODULE m_dll;
};