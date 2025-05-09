#include "cmd_executor.cpp"
#include "gmock/gmock.h"

class CmdExecutorFixture : public testing::Test {
public:
	CmdExecutor cmdExecutor;

	string TEST_VALID_VALUE = "0x12341234";
	string TEST_INVAID_VALUE_FORMET = "12341234";
	string TEST_INVAID_VALUE_RANGE = "0x1234123er3e";
	string TEST_INVAID_VALUE_NUMBER = "0x123.1r3e";
};

TEST_F(CmdExecutorFixture, WriteMain) {
	cmdExecutor.write(3, "0x12341234");

	EXPECT_NO_THROW(std::exception);
}

TEST_F(CmdExecutorFixture, WriteOutOfLBA) {
	EXPECT_THROW(cmdExecutor.write(101, TEST_VALID_VALUE), std::exception);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueFormat) {
	EXPECT_THROW(cmdExecutor.write(3, TEST_INVAID_VALUE_FORMET), std::exception);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueRange) {
	EXPECT_THROW(cmdExecutor.write(3, TEST_INVAID_VALUE_RANGE), std::exception);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueNumber) {
	EXPECT_THROW(cmdExecutor.write(3, TEST_INVAID_VALUE_NUMBER), std::exception);
}

TEST_F(CmdExecutorFixture, ReadMain) {
	cmdExecutor.write(3, "0x12341234");

	string ret = cmdExecutor.read(3);

	EXPECT_EQ("0x12341234", ret);
}


