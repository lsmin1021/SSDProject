#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"

TestShellApp::TestShellApp(SsdInterface* m_ssd): m_ssd(m_ssd) {
    CmdFactory::getInstance().setSdd(m_ssd);
}

bool TestShellApp::cmdParserAndExcute(const string& cmdString)
{
    vector<string> tokens = parseCmd(cmdString);
    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(tokens[0]);
    cmdObj->checkInvalidCmd(tokens);
    cmdObj->excuteCmd(tokens);

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