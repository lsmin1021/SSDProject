#include "cmd_executer.cpp"
#include "gmock/gmock.h"


TEST(TS, TC1) {
	CmdExecuter cmdExecuter;

	cmdExecuter.write(3, "0x12341234");

	EXPECT_NO_THROW(std::exception);
}
