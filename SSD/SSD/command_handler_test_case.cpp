#include "gmock/gmock.h"
#include "command_handler.cpp"

class CommandHandlerFixture : public testing::Test {
public:
	void isValidCommand(bool expected, const vector<string>& cmd) {
		bool actual = app.isValidCommand(cmd);

		EXPECT_EQ(expected, actual);
	}

	CommandHandler app;
	
	const string WRITE_COMMAND = "W";
	const string VALID_LBA = "0";
	const string VALID_VALUE = "0x12345678";
};

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Success) {
	isValidCommand(true, { WRITE_COMMAND, VALID_LBA, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_LessArgument) {
	isValidCommand(false, { WRITE_COMMAND, VALID_LBA });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_LargeValue) {
	isValidCommand(false, { WRITE_COMMAND, "120", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NegativeValue) {
	isValidCommand(false, { WRITE_COMMAND, "-1", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger1) {
	isValidCommand(false, { WRITE_COMMAND, "3.14", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger2) {
	isValidCommand(false, { WRITE_COMMAND, "abc", VALID_VALUE });
}