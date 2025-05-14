#include "gmock/gmock.h"
#include "command_handler.h"

using namespace testing;

class CommandHandlerFixture : public Test {
protected:
	void SetUp() override {
		m_handler = new CommandHandler();
	}

public:
	void isValidCommand(const vector<string>& cmd) {
		EXPECT_TRUE(m_handler->handleCommand(cmd));
	}

	void isInvalidCommand(const vector<string>& cmd) {
		EXPECT_FALSE(m_handler->handleCommand(cmd));
	}

	void handleCommand(const vector<string>& cmd) {
		m_handler->handleCommand(cmd);
	}

	CommandHandler* m_handler = nullptr;

	const string DIR_NAME = "buffer";
	const string WRITE_COMMAND = "W";
	const string READ_COMMAND = "R";
	const string ERASE_COMMAND = "E";
	const string FLUSH_COMMAND = "F";
	const string VALID_LBA = "0";
	const string INVALID_LBA = "100";
	const string VALID_ERASE_SIZE = "10";
	const string INVALID_ERASE_SIZE = "11";
	const string VALID_VALUE = "0x1A2B3E4F";
	const string EMPTY_VALUE = "0x00000000";

	const vector<string> VALID_WRITE_CMD = { WRITE_COMMAND, VALID_LBA, VALID_VALUE };
	const vector<string> INVALID_WRITE_CMD = { WRITE_COMMAND, VALID_LBA, VALID_VALUE , VALID_VALUE };
	const vector<string> VALID_READ_CMD = { READ_COMMAND, VALID_LBA };
	const vector<string> INVALID_READ_CMD = { READ_COMMAND, VALID_LBA, VALID_LBA};
	const vector<string> VALID_ERASE_CMD = { ERASE_COMMAND, VALID_LBA, VALID_ERASE_SIZE };
	const vector<string> INVALID_ERASE_CMD_SIZE_ERROR = { ERASE_COMMAND, VALID_LBA, INVALID_ERASE_SIZE };
	const vector<string> INVALID_ERASE_CMD_LBA_ERROR = { ERASE_COMMAND, INVALID_LBA, INVALID_ERASE_SIZE };
	const vector<string> INVALID_ERASE_CMD_ARGUMENT_ERROR = { ERASE_COMMAND, VALID_LBA, VALID_ERASE_SIZE,  VALID_ERASE_SIZE };
	const vector<string> VALID_FLUSH_CMD = { FLUSH_COMMAND };
	const vector<string> INVALID_FLUSH_CMD = { FLUSH_COMMAND, VALID_LBA };
};

TEST_F(CommandHandlerFixture, WriteValidCheckSuccess) {
	isValidCommand(VALID_WRITE_CMD);
}

TEST_F(CommandHandlerFixture, WriteValidCheckFail_InvalidArgumentCount) {
	isInvalidCommand({ });
	isInvalidCommand({ WRITE_COMMAND });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA });
	isInvalidCommand({ WRITE_COMMAND, VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, VALID_VALUE, VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, WRITE_COMMAND, VALID_LBA, VALID_VALUE, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, WriteValidCheckFail_InvalidLBA) {
	isInvalidCommand({ WRITE_COMMAND, "120", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "9999", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "3.14", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "abc", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "123fe", VALID_VALUE });
	isInvalidCommand({ WRITE_COMMAND, "0.2", VALID_VALUE });
}

TEST_F(CommandHandlerFixture, WriteValidCheckFail_InvalidValue) {
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "00000000" });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "0x0000" });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "0x1234567890" });
	isInvalidCommand({ WRITE_COMMAND, VALID_LBA, "0x12345XYZ" });
}

TEST_F(CommandHandlerFixture, ReadValidCheckSuccess) {
	isValidCommand(VALID_READ_CMD);
}

TEST_F(CommandHandlerFixture, ReadValidCheckFail_InvalidArgumentCount) {
	isInvalidCommand({ });
	isInvalidCommand({ READ_COMMAND });
	isInvalidCommand({ READ_COMMAND, VALID_LBA, VALID_VALUE });
	isInvalidCommand({ READ_COMMAND, READ_COMMAND, VALID_LBA, VALID_VALUE });
}

TEST_F(CommandHandlerFixture, ReadValidCheckFail_InvalidLBA) {
	isInvalidCommand({ READ_COMMAND, "120", VALID_VALUE });
	isInvalidCommand({ READ_COMMAND, "9999", VALID_VALUE });
	isInvalidCommand({ READ_COMMAND, "3.14" });
	isInvalidCommand({ READ_COMMAND, "abc" });
	isInvalidCommand({ READ_COMMAND, "123fe" });
	isInvalidCommand({ READ_COMMAND, "0.2" });
}

TEST_F(CommandHandlerFixture, EraseValidCheckSuccess) {
	isValidCommand(VALID_ERASE_CMD);
}

TEST_F(CommandHandlerFixture, EraseValidCheckFail_InvalidValue) {
	isInvalidCommand(INVALID_ERASE_CMD_SIZE_ERROR);
	isInvalidCommand(INVALID_ERASE_CMD_LBA_ERROR);
}

TEST_F(CommandHandlerFixture, EraseValidCheckFail_InvalidArgumentCount) {
	isInvalidCommand(INVALID_ERASE_CMD_ARGUMENT_ERROR);
}

TEST_F(CommandHandlerFixture, FlushValidCheckSuccess) {
	isValidCommand(VALID_FLUSH_CMD);
}

TEST_F(CommandHandlerFixture, FlushValidCheckFail_InvalidArgumentCount) {
	isInvalidCommand(INVALID_FLUSH_CMD);
}

/*

TEST_F(CommandHandlerFixture, WriteCommandExecute) {
	EXPECT_CALL(m_mockNand, write).Times(1);

	handleCommand(VALID_WRITE_CMD);
}

TEST_F(CommandHandlerFixture, ReadCommandExecute) {
	EXPECT_CALL(m_mockNand, read)
		.Times(1)
		.WillRepeatedly(Return(VALID_VALUE));

	handleCommand(VALID_READ_CMD);
}

TEST_F(CommandHandlerFixture, HandleWriteCommand) {
	EXPECT_CALL(m_mockNand, write).Times(1);

	handleCommand(VALID_WRITE_CMD);
}

TEST_F(CommandHandlerFixture, HandleReadCommand) {
	EXPECT_CALL(m_mockNand, read)
		.Times(1)
		.WillRepeatedly(Return(VALID_VALUE));

	handleCommand(VALID_READ_CMD);
}

TEST_F(CommandHandlerFixture, HandleInvalidCommand) {
	EXPECT_CALL(m_mockNand, read).Times(0);
	EXPECT_CALL(m_mockNand, write).Times(0);

	handleCommand(INVALID_READ_CMD);
	handleCommand(INVALID_WRITE_CMD);
}
*/