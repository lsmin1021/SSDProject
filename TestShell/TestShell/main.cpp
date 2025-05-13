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
	SsdDriver ssd;
	TestShellApp app{ &ssd };

	if (argc > 1) {
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
			catch (const std::invalid_argument& e) {
				std::cout << "FAIL" << std::endl;
				break;
			}
			catch (const FailException& e) {
				break;
			}
		}
		file.close();
	}
	else {
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
			catch (const std::invalid_argument& e) {
				cout << "INVALID COMMAND\n";
			}
			catch (const FailException& e) {
			}
			catch (const ExitException& e) {
				break;
			}

			std::cout << std::endl;
		}
	}
	return 0;
#endif
}
