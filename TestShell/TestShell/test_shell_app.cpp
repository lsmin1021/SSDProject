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

bool TestShellApp::cmdParserAndExcute(const string& cmdString)
{
    vector<string> tokens = parseCmd(cmdString);
    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }
    
    bool result = CmdExecuter::getInstance().executeCmd(tokens);
    if (result) return true;
    
    string cmdName = tokens[0];
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
            cmdParserAndExcute(input);
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
            cmdParserAndExcute(line);
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