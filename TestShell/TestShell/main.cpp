#include <iostream>
#ifdef _DEBUG
#include <gmock/gmock.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _DEBUG
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#else
    std::cout << "Production code 실행!" << std::endl;
    // production logic 실행
    return 0;
#endif
}
