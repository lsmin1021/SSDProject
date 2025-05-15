#include "testscript_dll_driver.h"
#include "testscript_factory.h"
#include "testscript_interface.h"

TsDllDriver::TsDllDriver(AppCb* appCb) {
    const string& folderPath = ".\\";
    vector<string> dllFileNames = getDllFileNames(folderPath);
    for (auto fileName : dllFileNames) {
        openTestShellLib(appCb, fileName);
    }
}

TsDllDriver& TsDllDriver::getInstance(AppCb* appCb)
{
    static TsDllDriver instance(appCb);
    return instance;
}


void TsDllDriver::openTestShellLib(AppCb* appCb, string dllFileName) {
    GetInstance getInstance = getInstanceApi(dllFileName);
    if (getInstance == nullptr) return;
    TestScriptFactory::getInstance().registerTs(getInstance(appCb));
}

GetInstance TsDllDriver::getInstanceApi(string flleName){
    HMODULE m_dll = LoadLibraryA(flleName.c_str());
    if (m_dll == nullptr) {
        std::cerr << "TsDllDriver load fail!" << std::endl;
        return nullptr;
    }
    GetInstance getInstance = (GetInstance)GetProcAddress(m_dll, "getInstance");
    if (getInstance == nullptr) {
        std::cerr << "getInstance symbol search fali!" << std::endl;
        FreeLibrary(m_dll);
        return nullptr;
    }
    return getInstance;
}

std::vector<std::string> TsDllDriver::getDllFileNames(const std::string& folderPath) {
    std::vector<std::string> dllFiles;
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((folderPath + "\\*.dll").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            dllFiles.push_back(folderPath + "\\" + findFileData.cFileName);
        } while (FindNextFileA(hFind, &findFileData));

        FindClose(hFind);
    }
    return dllFiles;
}