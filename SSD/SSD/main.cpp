#include <iostream>
#ifdef _DEBUG
#include <gmock/gmock.h>
#endif
#include "command_handler.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
#else
	std::vector<std::string> cmd;
	for (int i = 1; i < argc; ++i) { // argv[0]는 실행 파일 이름
		cmd.emplace_back(argv[i]);
	}

	CommandHandler app;
	app.handleCommand(cmd);

	return 0;
#endif
}
