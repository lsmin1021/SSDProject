#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"
#include "testscript_factory.h"

#include <windows.h>
typedef void (*RegisterTs)(void);


TestShellApp::TestShellApp(SsdInterface* ssd): m_ssd(ssd) {
    CmdFactory::getInstance().setSdd(ssd);

    HMODULE hDll = LoadLibraryA("TestShellLib.dll");
    if (hDll == nullptr) {
        std::cerr << "DLL load fail!" << std::endl;
        return;
    }
    RegisterTs registerTs = (RegisterTs)GetProcAddress(hDll, "registerTs");
    if (registerTs == nullptr) {
        std::cerr << "registerTs symbol search fali!" << std::endl;
    }
    else {
        registerTs();
    }

    m_executeTs = (ExecuteTs)GetProcAddress(hDll, "executeTs");
    if (m_executeTs == nullptr) {
        std::cerr << "setSdd symbol search fali!" << std::endl;
    }
}
TestShellApp::~TestShellApp(){
    //FreeLibrary(hDll);
}
bool TestShellApp::cmdParserAndExcute(const string& cmdString)
{
    vector<string> tokens = parseCmd(cmdString);
    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }
    string cmdName = tokens[0];
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(cmdName);
    if (cmdObj != nullptr)
    {
        cmdObj->checkInvalidCmd(tokens);
        cmdObj->excuteCmd(tokens);
        return true;
    }
    m_executeTs(cmdName.c_str());
    return true;
}

vector<string>  TestShellApp::parseCmd(const string& cmd) {
    std::istringstream iss(cmd);
    vector<string> tokens;
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}