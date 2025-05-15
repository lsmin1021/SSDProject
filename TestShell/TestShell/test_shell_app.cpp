#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"
#include "cmd_executer.h"
#include "msg_handler.h"
#include "console_handler.h"
#include "file_output_handler.h"
#include "dll_driver.h"
#include <windows.h>
#include "logger.h"

TestShellApp::TestShellApp(SsdInterface* m_ssd): m_ssd(m_ssd), m_shellMode(MODE_NULL) {
    CmdFactory::getInstance().setSdd(m_ssd);
    DllDriver::getInstance().openDll();
}

void TestShellApp::run(int argc, char* argv[]) {
    if (argc == 1) {
        setShellMode(MODE_BASIC);
        runBasicMode();
    }
    else if (argc == 2) {
        setShellMode(MODE_RUNNER);
        runRunnerMode(argv[1]);
    }
    else {
        printInvalidArgsMessage(argv[0]);
    }
}

void TestShellApp::runBasicMode(void) {
    ConsoleOutputHandler outputHandler;
    MsgHandler::getInstance().setMsgHandler(&outputHandler);
    
    string input;
    while (true) {
        MSG_PRINT("Shell> ");
        std::getline(std::cin, input);

        if (input.empty()) {
            MSG_PRINT("\n");
            continue;
        }

        try {
            cmdParserAndExecute(input);
        }
        catch (const std::invalid_argument&) {
            MSG_PRINT("INVALID COMMAND\n");
        }
        catch (const FailException&) {
            MSG_PRINT("FAIL\n");
        }
        catch (const ExitException&) {
            break;
        }

        MSG_PRINT("\n");
    }
}

void TestShellApp::runRunnerMode(const string& scriptFileName) {
    FileOutputHandler outputHandler;
    MsgHandler::getInstance().setMsgHandler(&outputHandler);

    std::ifstream file(scriptFileName);
    if (!file) {
        std::cerr << "Error: Unable to open file " << scriptFileName << std::endl;
        return;
    }

    string line;
    while (std::getline(file, line)) {
        std::cout << line << "  ---  Run...";

        try {
            cmdParserAndExecute(line);
        }
        catch (const std::invalid_argument&) {
            std::cout << "FAIL!" << std::endl;
            break;
        }
        catch (const FailException&) {
            std::cout << "FAIL!" << std::endl;
            break;
        }
        catch (const ExitException&) {
            std::cout << "EXIT" << std::endl;
            break;
        }
    }
    file.close();
}

bool TestShellApp::cmdParserAndExecute(const string& cmdString) {
    vector<string> cmdTokens = parseCmd(cmdString);
    if (cmdTokens.empty()) {
        LOG_PRINT("TestShellApp", "Empty command\n");
        throw std::invalid_argument("Empty command");
    }    
    
    if (executeSsdComand(cmdTokens)) {
        if (getShellMode() == MODE_RUNNER) {
            std::cout << "PASS" << std::endl;
        }
        return true;
    }
    executeTestScript(cmdTokens);

    return true;
}

static vector<string> tsTokensToDll;
void TestShellApp::executeTestScript(const vector<string>& tsTokens) {
    tsTokensToDll = tsTokens;
    DllDriver::getInstance().getDllApi().executeTs(tsTokensToDll);
    if (getShellMode() != MODE_NULL) {
        std::cout << "PASS\n";
    }
}

bool TestShellApp::executeSsdComand(vector<string> cmdTokens) {
    if (CmdExecuter::getInstance().executeCmd(cmdTokens)) {
        return true;
    }
    return false;
}

vector<string> TestShellApp::parseCmd(const string& cmdString) {
    std::istringstream iss(cmdString);
    vector<string> cmdTokens;
    string token;

    while (iss >> token) {
        cmdTokens.push_back(token);
    }
    return cmdTokens;
}

void TestShellApp::printInvalidArgsMessage(const std::string& programName) {
    std::cerr << "Error: Invalid arguments for Runner Mode.\n";
    std::cerr << "Usage: " << programName << " <scripts_file>\n";
}