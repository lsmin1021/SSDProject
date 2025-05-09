#include "cmd_executor.cpp"
#include "gmock/gmock.h"

TEST(CommandExecutor, WriteMain) {
	CmdExecutor cmdExecutor;

	cmdExecutor.write(3, "0x12341234");

	EXPECT_NO_THROW(std::exception);
}

TEST(CommandExecutor, WriteOutOfLBA) {
	CmdExecutor cmdExecutor;

	EXPECT_THROW(cmdExecutor.write(101, "0x12341234"), std::exception);
}