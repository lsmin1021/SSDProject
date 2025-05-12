#include "gmock/gmock.h"
#include "command_handler.cpp"

using namespace testing;

class m_mockNand : public NandHandler {
public:
	MOCK_METHOD(void, read, (), (override));
	MOCK_METHOD(void, write, (int, string), (override));
	MOCK_METHOD(string, getData, (int), (override));
};

class CommandHandlerFixture : public Test {
protected:
	void SetUp() override {
		m_handler = new CommandHandler(&m_mockNand);
	}
public:
	void isValidCommand(const vector<string>& cmd) {
		EXPECT_TRUE(m_handler->isValidCommand(cmd));
	}

	void isInvalidCommand(const vector<string>& cmd) {
		EXPECT_FALSE(m_handler->isValidCommand(cmd));
	}

	void execute(const vector<string>& cmd) {
		m_handler->executeCommand(cmd);
	}

	void handleCommand(const vector<string>& cmd) {
		m_handler->handleCommand(cmd);
	}


	CommandHandler* m_handler = nullptr;
	NiceMock<m_mockNand> m_mockNand;

	const string WRITE_COMMAND = "W";
	const string READ_COMMAND = "R";
	const string VALID_LBA = "0";
	const string VALID_VALUE = "0x1A2B3E4F";
	const string EMPTY_VALUE = "0x00000000";

	const vector<string> VALID_WRITE_CMD = { WRITE_COMMAND, VALID_LBA, VALID_VALUE };
	const vector<string> INVALID_WRITE_CMD = { WRITE_COMMAND, VALID_LBA, VALID_VALUE , VALID_VALUE };
	const vector<string> VALID_READ_CMD = { READ_COMMAND, VALID_LBA };
	const vector<string> INVALID_READ_CMD = { READ_COMMAND, VALID_LBA, VALID_LBA};
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

TEST_F(CommandHandlerFixture, WriteCommandExecute) {
	EXPECT_CALL(m_mockNand, read).Times(1);
	EXPECT_CALL(m_mockNand, write).Times(1);

	execute(VALID_WRITE_CMD);
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

TEST_F(CommandHandlerFixture, ReadCommandExecute) {
	EXPECT_CALL(m_mockNand, getData)
		.Times(1)
		.WillRepeatedly(Return(VALID_VALUE));

	execute(VALID_READ_CMD);
}

TEST_F(CommandHandlerFixture, HandleWriteCommand) {
	EXPECT_CALL(m_mockNand, read).Times(1);
	EXPECT_CALL(m_mockNand, write).Times(1);

	handleCommand(VALID_WRITE_CMD);
}

TEST_F(CommandHandlerFixture, HandleReadCommand) {
	EXPECT_CALL(m_mockNand, read).Times(1);
	EXPECT_CALL(m_mockNand, getData)
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