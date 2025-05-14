#include <iostream>
#ifdef _DEBUG
#include <gmock/gmock.h>
#endif
#include <iostream>
#include <string>
#include "test_shell_app.h"
#include "ssd_driver.h"
#include "console_handler.h"
#include "file_output_handler.h"
#include "exit_cmd.h"
#include "msg_handler.h"
using std::string;

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
#else
	SsdDriver ssd;
	TestShellApp app{ &ssd };
	if (argc > 1) {
		FileOutputHandler outputHandler;
		MsgHandler::getInstance().setMsgHandler(&outputHandler);

		std::ifstream file(argv[1]);
		if (!file) {
			std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
			return 1;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::cout << line << "  ---  Run...";

			try {
				app.cmdParserAndExcute(line);
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
	else {
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
				app.cmdParserAndExcute(input);
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
	return 0;
#endif
}
