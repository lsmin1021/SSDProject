#include "gmock/gmock.h"
#include "command_handler.cpp"

TEST(CommandHandler, ValidWriteCommand) {
	CommandHandler app;
	
	vector<string> cmd = { "W", "0", "0x12345678" };

	bool expected = true;
	bool actual = app.isValidCommand(cmd);
	EXPECT_EQ(expected, actual);
}