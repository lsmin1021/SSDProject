#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"
#include "dll_driver.h"
#include <windows.h>

TestShellApp::TestShellApp(SsdInterface* m_ssd): m_ssd(m_ssd) {
    CmdFactory::getInstance().setSdd(m_ssd);
    DllDriver::getInstance().openDll();
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
    DllDriver::getInstance().getDllApi().executeTs(cmdName.c_str());

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