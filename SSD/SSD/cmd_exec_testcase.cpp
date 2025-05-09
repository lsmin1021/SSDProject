#include "cmd_executor.cpp"
#include "gmock/gmock.h"

using namespace testing;

class MockNandHandler : public FileHandler {
public:
	MOCK_METHOD(string, read, (), (override));
	MOCK_METHOD(void, write, (string), (override));
};

class CmdExecutorFixture : public Test {
protected:
	void SetUp() override {
		cmdExecutor.setNandHandler(&mockHandler);
		cmdExecutor.setOutputHandler(&mockHandler);
	}

public:
	CmdExecutor cmdExecutor;
	NiceMock<MockNandHandler> mockHandler;

	const string VALID_VALUE = "0x12341234";
	const string EMPTY_VALUE = "0x00000000";
	const string INVAID_VALUE_FORMET = "12341234";
	const string INVAID_VALUE_RANGE = "0x1234123er3e";
	const string INVAID_VALUE_NUMBER = "0x123.1r3e";
};

TEST_F(CmdExecutorFixture, WriteMain) {
	cmdExecutor.write(3, VALID_VALUE);

	EXPECT_NO_THROW(std::exception);
}

TEST_F(CmdExecutorFixture, WriteOutOfLBA) {
	EXPECT_THROW(cmdExecutor.write(101, VALID_VALUE), std::exception);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueFormat) {
	EXPECT_THROW(cmdExecutor.write(3, INVAID_VALUE_FORMET), std::exception);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueRange) {
	EXPECT_THROW(cmdExecutor.write(3, INVAID_VALUE_RANGE), std::exception);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueNumber) {
	EXPECT_THROW(cmdExecutor.write(3, INVAID_VALUE_NUMBER), std::exception);
}

TEST_F(CmdExecutorFixture, ReadMain) {
	cmdExecutor.write(3, VALID_VALUE);

	string ret = cmdExecutor.read(3);

	EXPECT_EQ(VALID_VALUE, ret);
}

TEST_F(CmdExecutorFixture, ReadEmptyLBA) {
	string ret = cmdExecutor.read(3);

	EXPECT_EQ(EMPTY_VALUE, ret);
}

TEST_F(CmdExecutorFixture, ReadOutOfLBA) {
	cmdExecutor.write(3, VALID_VALUE);

	EXPECT_THROW(cmdExecutor.read(101), std::exception);
}

TEST_F(CmdExecutorFixture, StoreWrittenValue) {
	EXPECT_CALL(mockHandler, write).Times(1);

	cmdExecutor.write(3, VALID_VALUE);
}