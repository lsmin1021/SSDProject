#include <iostream>
#ifdef _DEBUG
#include <gmock/gmock.h>
#endif
#include "test_shell_app.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#else
    //TestShellApp testShell{ssdInterface};
    //testShell.argParser(&argc, argv);

    return 0;
#endif
}
