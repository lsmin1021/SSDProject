#include "gmock/gmock.h"
#include "command_handler.cpp"

TEST(CommandHandler, ValidCommandCheck_Write_Success) {
	CommandHandler app;
	
	vector<string> cmd = { "W", "0", "0x12345678" };

	bool expected = true;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}

TEST(CommandHandler, ValidCommandCheck_Read_Success) {
	CommandHandler app;

	vector<string> cmd = { "R", "0" };

	bool expected = true;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}

TEST(CommandHandler, ValidCommandCheck_Write_Fail) {
	CommandHandler app;

	vector<string> cmd = { "W", "0" };

	bool expected = false;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}
