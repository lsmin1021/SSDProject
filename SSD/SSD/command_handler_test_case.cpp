#include "gmock/gmock.h"
#include "command_handler.cpp"

class CommandHandlerFixture : public testing::Test {
public:
	void isValidCommand(bool expected, const vector<string>& cmd) {
		bool actual = app.isValidCommand(cmd);

		EXPECT_EQ(expected, actual);
	}

	CommandHandler app;
};

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Success) {
	vector<string> cmd = { "W", "0", "0x12345678" };
	isValidCommand(true, cmd);
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_LessArgument) {
	vector<string> cmd = { "W", "0" };
	isValidCommand(false, cmd);
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_LargeValue) {
	vector<string> cmd = { "W", "120", "0x12345678" };
	isValidCommand(false, cmd);
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NegativeValue) {
	vector<string> cmd = { "W", "-1", "0x12345678" };
	isValidCommand(false, cmd);
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger1) {
	vector<string> cmd = { "W", "3.14", "0x12345678" };
	isValidCommand(false, cmd);
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger2) {
	vector<string> cmd = { "W", "abc", "0x12345678" };
	isValidCommand(false, cmd);
}