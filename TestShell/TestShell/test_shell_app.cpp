#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"
#include "testscript_factory.h"

TestShellApp::TestShellApp(SsdInterface* m_ssd): m_ssd(m_ssd) {
    CmdFactory::getInstance().setSdd(m_ssd);
}

bool TestShellApp::cmdParserAndExcute(const string& cmdString)
{
    vector<string> tokens = parseCmd(cmdString);
    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }
    TsInterface* tsObj;
    bool isTS = true;
    bool isCmd = true;
    try {
        tsObj = TestScriptFactory::getInstance().getCmd(tokens[0].substr(0, 2));
        tsObj->checkInvalidCmd(tokens);
        tsObj->excuteCmd(tokens);
    }
    catch (const std::invalid_argument& e) {
        isTS = false;
    }
    if (isTS == false) {
        CmdInterface* cmdObj;
        try {
            cmdObj = CmdFactory::getInstance().getCmd(tokens[0]);
            cmdObj->checkInvalidCmd(tokens);
            cmdObj->excuteCmd(tokens);
        }
        catch (const std::invalid_argument& e) {
            isCmd = false;
        }
    }

    if (!isTS && !isCmd) {
        throw std::invalid_argument("Invalid command: " + tokens[0]);
    }

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