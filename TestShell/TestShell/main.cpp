#include <iostream>
#ifdef _DEBUG
#include <gmock/gmock.h>
#endif
#include <iostream>
#include <string>
#include "test_shell_app.h"
#include "ssd_driver.h"
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
        std::getline(std::cin, input);  // �� �� �Է� �޾� input�� ����

        if (input.empty()) {
            std::cout << std::endl;
            continue;  // �ƹ� ó���� ���� �ʰ� ���� ������
        }

        app.cmdParserAndExcute(input);

        if (input == "exit") {
            break;
        }

        std::cout << std::endl;
    }
    return 0;
#endif
}
