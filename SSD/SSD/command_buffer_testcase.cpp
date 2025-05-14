#include "gmock/gmock.h"
#include "command_handler.h"
#include "command_buffer.h"
#include "nand_storage.h"

using namespace testing;

class MockNandHandler : public NandStorage {
	MOCK_METHOD(string, read, (int), ());
};

class CommandBufferFixture : public Test {
protected:
	void SetUp() override {
		m_handler = new CommandHandler();
	}

	void TearDown() override {
		m_handler->handleCommand({ FLUSH_COMMAND });
	}
public:
	void runTest(
		const vector<vector<string>>& commands,
		const vector<string>& expectedResult)
	{
		for (const auto& cmd : commands)
			m_handler->handleCommand(cmd);

		EXPECT_EQ(m_fileHandler.getFileList(DIR_NAME), expectedResult);
	}

	CommandHandler* m_handler = nullptr;
	FileHandler m_fileHandler;

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
	const vector<string> INVALID_READ_CMD = { READ_COMMAND, VALID_LBA, VALID_LBA };
	const vector<string> VALID_ERASE_CMD = { ERASE_COMMAND, VALID_LBA, VALID_ERASE_SIZE };
	const vector<string> INVALID_ERASE_CMD_SIZE_ERROR = { ERASE_COMMAND, VALID_LBA, INVALID_ERASE_SIZE };
	const vector<string> INVALID_ERASE_CMD_LBA_ERROR = { ERASE_COMMAND, INVALID_LBA, INVALID_ERASE_SIZE };
	const vector<string> INVALID_ERASE_CMD_ARGUMENT_ERROR = { ERASE_COMMAND, VALID_LBA, VALID_ERASE_SIZE,  VALID_ERASE_SIZE };
	const vector<string> VALID_FLUSH_CMD = { FLUSH_COMMAND };
	const vector<string> INVALID_FLUSH_CMD = { FLUSH_COMMAND, VALID_LBA };
};

TEST_F(CommandBufferFixture, IgnoreCommand_IgnoreWrite) {
	vector<string> expected = {
		"0_W_21_0x12341234",
		"1_W_20_0xEEEEFFFF",
		"2_empty",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ WRITE_COMMAND, "20", "0xABCDABCD" },
		{ WRITE_COMMAND, "21", "0x12341234" },
		{ WRITE_COMMAND, "20", "0xEEEEFFFF" }
		},
		expected);
}

TEST_F(CommandBufferFixture, IgnoreCommand_IgnoreEraseAndWrite) {
	vector<string> expected = {
		"0_E_18_5",
		"1_empty",
		"2_empty",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "18", "3" },
		{ WRITE_COMMAND, "21", "0x12341234" },
		{ ERASE_COMMAND, "18", "5" }
		},
		expected);
}

TEST_F(CommandBufferFixture, MergeErase_Basic) {
	vector<string> expected = {
		"0_W_20_0xABCDABCD",
		"1_E_10_5",
		"2_empty",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ WRITE_COMMAND, "20", "0xABCDABCD" },
		{ ERASE_COMMAND, "10", "4" },
		{ ERASE_COMMAND, "12", "3" }
		},
		expected);
}


TEST_F(CommandBufferFixture, FastRead_Basic) {
	vector<string> expected = {
		"0_E_10_2",
		"1_W_11_0xABCDABCD",
		"2_empty",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ WRITE_COMMAND, "10", "0xABCDABCD" },
		{ ERASE_COMMAND, "10", "2" },
		{ WRITE_COMMAND, "11", "0xABCDABCD" }
		},
		expected);
}

TEST_F(CommandBufferFixture, EraseMergeAndIgnoreWrite) {
	vector<string> expected = {
		"0_E_10_4",
		"1_W_11_0xABCDABCD",
		"2_W_12_0x12341234",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "10", "3" },
		{ ERASE_COMMAND, "12", "2" },
		{ WRITE_COMMAND, "11", "0xABCDABCD" },
		{ WRITE_COMMAND, "11", "0xABCDABCD" },
		{ WRITE_COMMAND, "12", "0x12341234" }
		},
		expected);
}

TEST_F(CommandBufferFixture, FullIgnoreWrites) {
	vector<string> expected = {
		"0_W_21_0x12341234",
		"1_W_20_0xABCDABCD",
		"2_empty",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ WRITE_COMMAND, "20", "0xABCDABCD" },
		{ WRITE_COMMAND, "21", "0xABCDABCD" },
		{ WRITE_COMMAND, "20", "0x12341234" },
		{ WRITE_COMMAND, "21", "0x12341234" },
		{ WRITE_COMMAND, "20", "0xABCDABCD" }
		},
		expected);
}

TEST_F(CommandBufferFixture, FullEraseMerge) {
	vector<string> expected = {
		"0_E_0_6",
		"1_W_20_0xABCDABCD",
		"2_empty",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "0", "2" },
		{ ERASE_COMMAND, "2", "2" },
		{ ERASE_COMMAND, "3", "2" },
		{ ERASE_COMMAND, "5", "1" },
		{ WRITE_COMMAND, "20", "0xABCDABCD" }
		},
		expected);
}

TEST_F(CommandBufferFixture, FullWrites) {
	vector<string> expected = {
		"0_W_20_0xABCDABCD",
		"1_empty",
		"2_empty",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ WRITE_COMMAND, "20", "0x12341234" },
		{ WRITE_COMMAND, "20", "0x12341234" },
		{ WRITE_COMMAND, "20", "0x12341234" },
		{ WRITE_COMMAND, "20", "0x12341234" },
		{ WRITE_COMMAND, "20", "0xABCDABCD" }
		},
		expected);
}

TEST_F(CommandBufferFixture, WriteAfterEraseWithMerge) {
	vector<string> expected = {
		  "0_E_40_5",
		  "1_W_44_0xDEAD1234",
		  "2_W_41_0xCAFEBABE",
		  "3_empty", 
		  "4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "40", "3" },
		{ ERASE_COMMAND, "43", "2" },
		{ WRITE_COMMAND, "41", "0xCAFEBABE" },
		{ WRITE_COMMAND, "44", "0xDEAD1234" },
		{ WRITE_COMMAND, "41", "0xCAFEBABE" }
		},
		expected);
}

TEST_F(CommandBufferFixture, WriteAfterEraseWithMerge2) {
	vector<string> expected = {
		"0_E_40_5",
		"1_W_44_0xDEAD1234",
		"2_W_41_0xCAFEBEEF",
		"3_empty",
		"4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "40", "3" },
		{ ERASE_COMMAND, "43", "2" },
		{ WRITE_COMMAND, "41", "0xCAFEBABE" },
		{ WRITE_COMMAND, "44", "0xDEAD1234" },
		{ WRITE_COMMAND, "41", "0xCAFEBEEF" }
		},
		expected);
}

TEST_F(CommandBufferFixture, OverlappingEraseMerge) {
	vector<string> expected = {
		"0_E_50_6",
		"1_W_60_0xDEAD1234",
		"2_W_61_0xCAFEBEEF", 
		"3_empty", 
		"4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "50", "4" },
		{ ERASE_COMMAND, "52", "4" },
		{ ERASE_COMMAND, "54", "2" },
		{ WRITE_COMMAND, "60", "0xDEAD1234" },
		{ WRITE_COMMAND, "61", "0xCAFEBEEF" }
		},
		expected);
}

TEST_F(CommandBufferFixture, InterleavedEraseAndWrite) {
	vector<string> expected = {
		"0_E_68_5",
		"1_W_71_0x22220000",
		"2_W_70_0x11110000",
		"3_E_72_1",
		"4_empty"
	};

	runTest({
		{ WRITE_COMMAND, "70", "0x11110000" },
		{ ERASE_COMMAND, "68", "5" },
		{ WRITE_COMMAND, "71", "0x22220000" },
		{ WRITE_COMMAND, "70", "0x11110000" },
		{ ERASE_COMMAND, "72", "1" }
		},
		expected);
}

TEST_F(CommandBufferFixture, OutOfOrderEraseMerge) {
	vector<string> expected = {
		"0_E_80_5",
		"1_W_85_0xDEADDEAD",
		"2_W_86_0xEEEEEEEE",
		"3_empty", "4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "80", "3" },
		{ WRITE_COMMAND, "85", "0xDEADDEAD" },
		{ ERASE_COMMAND, "83", "2" },
		{ WRITE_COMMAND, "85", "0xDEADDEAD" },
		{ WRITE_COMMAND, "86", "0xEEEEEEEE" }
		},
		expected);
}

TEST_F(CommandBufferFixture, EraseIgnoreWriteMerge) {
	vector<string> expected = {
		"0_E_90_4",
		"1_W_91_0xAAAA0000",
		"2_W_93_0xBBBB1111",
		"3_empty", "4_empty"
	};

	runTest({
		{ ERASE_COMMAND, "90", "4" },
		{ WRITE_COMMAND, "91", "0xAAAA0000" },
		{ ERASE_COMMAND, "92", "2" },
		{ WRITE_COMMAND, "93", "0xBBBB1111" },
		{ WRITE_COMMAND, "91", "0xAAAA0000" }
		},
		expected);
}

