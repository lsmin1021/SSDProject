#include <iostream>
#ifdef _DEBUG
#include <gmock/gmock.h>
#endif
#include <iostream>
#include <string>
#include "test_shell_app.h"
#include "ssd_driver.h"
#include "exit_cmd.h"
using std::string;

int main(int argc, char* argv[]) {
#ifdef _DEBUG
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#else
    //TestShellApp testShell{ssdInterface};
    //testShell.argParser(&argc, argv);
    string input;
    SsdDriver ssd;
    TestShellApp app{ &ssd };

    while (true) {
        std::cout << "Shell> ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << std::endl;
            continue;
        }

        try {
            app.cmdParserAndExcute(input);
        }
        catch (const std::invalid_argument& e) {
            cout << "INVALID COMMAND\n";
        }
        catch (const ExitException& e) {
            break;
        }

        std::cout << std::endl;
    }
    return 0;
#endif
}
