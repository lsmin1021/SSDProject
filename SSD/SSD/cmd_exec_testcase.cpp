#include "cmd_executor.cpp"
#include "gmock/gmock.h"

using namespace testing;

class MockNandHandler : public NandInterface {
public:
	MOCK_METHOD(void, read, (), (override));
	MOCK_METHOD(void, write, (int, string), (override));
	MOCK_METHOD(string, getData, (int), (override));
};

class CmdExecutorFixture : public Test {
protected:
	void SetUp() {
		cmdExecutor.setNandHandler(&mockHandler);
	}
public:
	CmdExecutor cmdExecutor;
	NiceMock<MockNandHandler> mockHandler;

	const string VALID_VALUE = "0x12341234";
	const string EMPTY_VALUE = "0x00000000";
	const string INVAID_VALUE_FORMET = "12341234";
	const string INVAID_VALUE_RANGE = "0x1234123er3e";
	const string INVAID_VALUE_NUMBER = "0x123.1r3e";

	const int EMPTY_LBA = 99;
	const int NOT_EMPTY_LBA = 3;
	const int OUT_OF_RANGE_LBA = 101;
};

TEST_F(CmdExecutorFixture, WriteMain) {
	EXPECT_CALL(mockHandler, read).Times(1);
	EXPECT_CALL(mockHandler, write).Times(1);

	EXPECT_NO_THROW(cmdExecutor.write(NOT_EMPTY_LBA, VALID_VALUE), std::exception);
}

TEST_F(CmdExecutorFixture, WriteOutOfLBA) {
	EXPECT_THROW(cmdExecutor.write(OUT_OF_RANGE_LBA, VALID_VALUE), std::out_of_range);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueFormat) {
	EXPECT_THROW(cmdExecutor.write(NOT_EMPTY_LBA, INVAID_VALUE_FORMET), std::invalid_argument);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueRange) {
	EXPECT_THROW(cmdExecutor.write(NOT_EMPTY_LBA, INVAID_VALUE_RANGE), std::invalid_argument);
}

TEST_F(CmdExecutorFixture, WriteInvalidValueNumber) {
	EXPECT_THROW(cmdExecutor.write(NOT_EMPTY_LBA, INVAID_VALUE_NUMBER), std::invalid_argument);
}

TEST_F(CmdExecutorFixture, ReadMain) {
	EXPECT_CALL(mockHandler, getData)
		.Times(1)
		.WillRepeatedly(Return(VALID_VALUE));

	string ret = cmdExecutor.read(NOT_EMPTY_LBA);

	EXPECT_EQ(VALID_VALUE, ret);
}

TEST_F(CmdExecutorFixture, ReadEmptyLBA) {
	EXPECT_CALL(mockHandler, getData)
		.Times(1)
		.WillRepeatedly(Return(EMPTY_VALUE));
	string ret = cmdExecutor.read(EMPTY_LBA);

	EXPECT_EQ(EMPTY_VALUE, ret);
}

TEST_F(CmdExecutorFixture, ReadOutOfLBA) {
	EXPECT_THROW(cmdExecutor.read(OUT_OF_RANGE_LBA), std::exception);
}
