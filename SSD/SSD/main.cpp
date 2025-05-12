#include <iostream>
#ifdef _DEBUG
#include <gmock/gmock.h>
#endif
#include "command_handler.cpp"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
#else
	CommandHandler app(new CmdExecutor());
	std::vector<std::string> cmd;
	for (int i = 1; i < argc; ++i) { // argv[0]는 실행 파일 이름
		cmd.emplace_back(argv[i]);
	}

	if (app.isValidCommand(cmd)) {
		app.execute(cmd);
	}
	else {
		app.isError();
	}
	// production logic 실행
	return 0;
#endif
}
