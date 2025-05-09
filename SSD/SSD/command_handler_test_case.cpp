#include "gmock/gmock.h"
#include "command_handler.cpp"

class CommandHandlerFixture : public testing::Test {
public:
	void isValidCommand(const vector<string>& cmd) {
		EXPECT_TRUE(m_handler.isValidCommand(cmd));
	}

	void isInvalidCommand(const vector<string>& cmd) {
		EXPECT_FALSE(m_handler.isValidCommand(cmd));
	}

	CommandHandler m_handler;
	
	const string WRITE_COMMAND = "W";
	const string READ_COMMAND = "R";
	const string VALID_LBA = "0";
	const string VALID_VALUE = "0x12345678";
};

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Success) {
	isValidCommand({ WRITE_COMMAND, VALID_LBA, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_LessArgument) {
	isInvalidCommand({});
	isInvalidCommand({ WRITE_COMMAND });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA });
	isInvalidCommand({ WRITE_COMMAND, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_ManyArgument) {
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, VALID_VALUE, VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, WRITE_COMMAND, VALID_LBA, VALID_VALUE, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_LargeValue) {
	isInvalidCommand({ WRITE_COMMAND, "120", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "9999", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NegativeValue) {
	isInvalidCommand({ WRITE_COMMAND, "-1", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidLBA_NotInteger) {
	isInvalidCommand({ WRITE_COMMAND, "3.14", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "abc", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "123fe", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "0.2", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Write_Fail_InvalidValue) {
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "00000000"});
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "0x0000" });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "0x1234567890" });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "0x12345XYZ" });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Read_Success) {
	isValidCommand({ READ_COMMAND, VALID_LBA});
}
/*
TEST_F(CommandHandlerFixture, ValidCommandCheck_Read_Fail_LessArgument) {
	isInvalidCommand({});
	isInvalidCommand({ READ_COMMAND });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Read_Fail_ManyArgument) {
	isInvalidCommand({ READ_COMMAND, VALID_LBA, VALID_VALUE });
	isInvalidCommand({ READ_COMMAND, READ_COMMAND, VALID_LBA, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Read_Fail_InvalidLBA_LargeValue) {
	isInvalidCommand({ READ_COMMAND, "120", VALID_VALUE });
	isInvalidCommand({ READ_COMMAND, "9999", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Read_Fail_InvalidLBA_NegativeValue) {
	isInvalidCommand({ READ_COMMAND, "-1", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ValidCommandCheck_Read_Fail_InvalidLBA_NotInteger) {
	isInvalidCommand({ READ_COMMAND, "3.14" });
	isInvalidCommand({ READ_COMMAND, "abc" });
	isInvalidCommand({ READ_COMMAND, "123fe" });
	isInvalidCommand({ READ_COMMAND, "0.2" });
}*/