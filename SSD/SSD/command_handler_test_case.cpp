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
	isValidCommand(false, {});
	isValidCommand(false, { WRITE_COMMAND });
	isValidCommand(false, { WRITE_COMMAND, VALID_LBA });
	isValidCommand(false, { WRITE_COMMAND, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_ManyArgument) {
	isValidCommand(false, { WRITE_COMMAND, VALID_LBA, VALID_VALUE, VALID_VALUE });
	isValidCommand(false, { WRITE_COMMAND, WRITE_COMMAND, VALID_LBA, VALID_VALUE, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_LargeValue) {
	isValidCommand(false, { WRITE_COMMAND, "120", VALID_VALUE });
	isValidCommand(false, { WRITE_COMMAND, "9999", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NegativeValue) {
	isValidCommand(false, { WRITE_COMMAND, "-1", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger) {
	isValidCommand(false, { WRITE_COMMAND, "3.14", VALID_VALUE });
	isValidCommand(false, { WRITE_COMMAND, "abc", VALID_VALUE });
	isValidCommand(false, { WRITE_COMMAND, "123fe", VALID_VALUE });
	isValidCommand(false, { WRITE_COMMAND, "0.2", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidValue) {
	isValidCommand(false, { WRITE_COMMAND, VALID_LBA, "00000000"});
	isValidCommand(false, { WRITE_COMMAND, VALID_LBA, "0x0000" });
	isValidCommand(false, { WRITE_COMMAND, VALID_LBA, "0x1234567890" });
	isValidCommand(false, { WRITE_COMMAND, VALID_LBA, "0x12345XYZ" });
}