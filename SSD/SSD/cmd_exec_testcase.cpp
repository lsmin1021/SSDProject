#include "cmd_executor.cpp"
#include "gmock/gmock.h"

class CmdExecutorFixture : public testing::Test {
public:
	CmdExecutor cmdExecutor;
};

TEST_F(CmdExecutorFixture, WriteMain) {
	cmdExecutor.write(3, "0x12341234");

	EXPECT_NO_THROW(std::exception);
}

TEST_F(CmdExecutorFixture, WriteOutOfLBA) {
	EXPECT_THROW(cmdExecutor.write(101, "0x12341234"), std::exception);
}