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
	SsdDriver ssd;
	TestShellApp app{ &ssd };
	
	app.run(argc, argv);
	
	return 0;
#endif
}
