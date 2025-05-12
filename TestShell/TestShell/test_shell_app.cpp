#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"

TestShellApp::TestShellApp(SsdInterface* m_ssd): m_ssd(m_ssd) {
    CmdFactory::getInstance().setSdd(m_ssd);
}

bool TestShellApp::cmdParserAndExcute(const string& cmdString)
{
    vector<string> tokens = parseCmd(autoCompleteCommand(cmdString));
    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(tokens[0]);
    cmdObj->checkInvalidCmd(tokens);
    cmdObj->excuteCmd(tokens);

    return true;
}

string TestShellApp::autoCompleteCommand(const string& input) {
    static std::unordered_map<string, string> autocompleteMap = {
        {"1_", "1_FullWriteAndReadCompare"},
        {"2_", "2_PartialLBAWrite"},
        {"3_", "3_WriteReadAging"}
        // 필요 시 더 추가
    };

    auto it = autocompleteMap.find(input);
    if (it != autocompleteMap.end()) {
        return it->second;
    }

    return input;
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