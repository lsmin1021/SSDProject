#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"
#include "cmd_executer.h"
#include "dll_driver.h"
#include <windows.h>

#include "exit_cmd.h"
#include "console_handler.h"
#include "file_output_handler.h"
#include "msg_handler.h"

TestShellApp::TestShellApp(SsdInterface* m_ssd): m_ssd(m_ssd) {
    CmdFactory::getInstance().setSdd(m_ssd);
    DllDriver::getInstance().openDll();
}

void TestShellApp::run(int argc, char* argv[]) {
    if (argc == 1) {
        runBasic();
    }
    else if (argc == 2) {
        runRunner(argv[1]);
    }
    else {
        std::cerr << "Error: Invalid arguments for Runner Mode.\n";
        std::cerr << "Usage: " << argv[0] << " <scripts_file>\n";
    }
}

void TestShellApp::runBasic(void) {
    ConsoleOutputHandler outputHandler;
    MsgHandler::getInstance().setMsgHandler(&outputHandler);
    string input;

    while (true) {
        std::cout << "Shell> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << std::endl;
            continue;
        }

        try {
            cmdParserAndExecute(input);
        }
        catch (const std::invalid_argument&) {
            cout << "INVALID COMMAND\n";
        }
        catch (const FailException&) {
        }
        catch (const ExitException&) {
            break;
        }

        std::cout << std::endl;
    }
}

void TestShellApp::runRunner(string scriptFileName) {
    FileOutputHandler outputHandler;
    MsgHandler::getInstance().setMsgHandler(&outputHandler);

    std::ifstream file(scriptFileName);
    if (!file) {
        std::cerr << "Error: Unable to open file " << scriptFileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "  ---  Run...";

        try {
            cmdParserAndExecute(line);
        }
        catch (const std::invalid_argument&) {
            std::cout << "FAIL" << std::endl;
            break;
        }
        catch (const FailException&) {
            break;
        }
    }
    file.close();
}

bool TestShellApp::cmdParserAndExecute(const string& cmdString)
{
    vector<string> cmdTokens = parseCmd(cmdString);
    if (cmdTokens.empty()) {
        throw std::invalid_argument("Empty command");
    }
    
    if (CmdExecuter::getInstance().executeCmd(cmdTokens)) return true;
    
    string cmdName = cmdTokens[0];
    DllDriver::getInstance().getDllApi().executeTs(cmdName.c_str());

    return true;
}

vector<string>  TestShellApp::parseCmd(const string& cmdString) {
    std::istringstream iss(cmdString);
    vector<string> cmdTokens;
    string token;

    while (iss >> token) {
        cmdTokens.push_back(token);
    }
    return cmdTokens;
}