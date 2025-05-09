#include "gmock/gmock.h"
#include "command_handler.cpp"

TEST(CommandHandler, ValidCommandCheck_Write_Success) {
	CommandHandler app;
	
	vector<string> cmd = { "W", "0", "0x12345678" };

	bool expected = true;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}

TEST(CommandHandler, ValidCommandCheck_Write_Fail_LessArgument) {
	CommandHandler app;

	vector<string> cmd = { "W", "0" };

	bool expected = false;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}

TEST(CommandHandler, ValidCommandCheck_Write_Fail_InvalidLBA_LargeValue) {
	CommandHandler app;

	vector<string> cmd = { "W", "120", "0x12345678"};

	bool expected = false;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}

TEST(CommandHandler, ValidCommandCheck_Write_Fail_InvalidLBA_NegativeValue) {
	CommandHandler app;

	vector<string> cmd = { "W", "-1", "0x12345678" };

	bool expected = false;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}

TEST(CommandHandler, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger1) {
	CommandHandler app;

	vector<string> cmd = { "W", "3.14", "0x12345678" };

	bool expected = false;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}

TEST(CommandHandler, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger2) {
	CommandHandler app;

	vector<string> cmd = { "W", "abc", "0x12345678" };

	bool expected = false;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}