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
        std::getline(std::cin, input);  // 한 줄 입력 받아 input에 저장

        if (input.empty()) {
            std::cout << std::endl;
            continue;  // 아무 처리도 하지 않고 다음 루프로
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
