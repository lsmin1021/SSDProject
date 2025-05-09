#include "cmd_executor.cpp"
#include "gmock/gmock.h"


TEST(CommandExecutor, TC1) {
	CmdExecutor cmdExecutor;

	cmdExecutor.write(3, "0x12341234");

	EXPECT_NO_THROW(std::exception);
}
