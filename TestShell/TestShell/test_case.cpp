#pragma once

#include <gmock/gmock.h>
#include "mock_ssd.h"
#include "ssd_driver.h"
#include "test_shell_app.h"
using namespace testing;

class MockSddFixture : public Test {
protected:
	void SetUp() {
		m_tespApp = new TestShellApp(&m_mockSsd);
	}

public:
	const string TEST_LBA = "0";
	const string TEST_DATA = "0x00000000";
	const string INVALID_CMD = "test";
	const string READ_SUCESS = "read 0";
	const string READ_FAIL_LESS_NUM_ARG = "read";
	const string READ_FAIL_MORE_NUM_ARG = "read 0 1";
	const string READ_FAIL_INVALID_LBA = "read 100";
	const string FULL_READ_SUCESS = "fullread";
	const string FULL_READ_FAIL_MORE_NUM_ARG = "fullread 100";
	const string WRITE_SUCESS = "write 0 0x00000000";
	const string WRITE_FAIL_LESS_NUM_ARG = "write 0";
	const string WRITE_FAIL_MORE_NUM_ARG = "write 0 0x00000000 9";
	const string WRITE_FAIL_SMALL_LEN_DATA = "write 0 0x1";
	const string WRITE_FAIL_BIC_LEN_DATA = "write 0 0x11111111111";
	const string WRITE_FAIL_NOT_HEX_DATA = "write 0 00000000";
	const string WRITE_FAIL_NOT_HEX_CHAR_DATA = "write 0 0xP0000000";
	const string FULL_WRITE_SUCESS = "fullwrite 0x00000000";
	const string FULL_WRITE_FAIL_LESS_NUM_ARG = "fullwrite";
	const string FULL_WRITE_FAIL_MORE_NUM_ARG = "fullwrite 0x00000000 o";
	const string FULL_WRITE_FAIL_INVALD_DATA= "fullwrite 0x00";
	const string HELP_CMD = "help";
	const string INVALID_HELP_CMD = "hel v";
	const string INVALID_EXIT_CMD = "exit 0";
	const string TEST_SCRIPT1 = "1_FullWriteAndReadCompare";
	const string TEST_SCRIPT1_SHORT_CUT = "1_";
	const string TEST_SCRIPT2 = "2_PartialLBAWrite";
	const string TEST_SCRIPT2_SHORT_CUT = "2_";
	const string TEST_SCRIPT3 = "3_WriteReadAging";
	const string TEST_SCRIPT3_SHORT_CUT = "3_";
	const int TEST_SCRIPT1_READ_WRITE_REPEAT_NUM = 100;
	const int TEST_SCRIPT2_READ_WRITE_REPEAT_NUM = 150;
	const int TEST_SCRIPT3_READ_WRITE_REPEAT_NUM = 400;
	NiceMock<MockSsd> m_mockSsd;
	TestShellApp* m_tespApp;
};

TEST_F(MockSddFixture, ReadSuccess) {
	// Arrange
	EXPECT_CALL(m_mockSsd, readData(TEST_LBA)).Times(1);
	// Act
	m_tespApp->cmdParserAndExcute(READ_SUCESS);
}

TEST_F(MockSddFixture, FullReadSuccess) {
	// Arrange
	EXPECT_CALL(m_mockSsd, readData(_)).Times(100);
	// Act
	m_tespApp->cmdParserAndExcute(FULL_READ_SUCESS);
}

TEST_F(MockSddFixture, WriteSucess) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(TEST_LBA, TEST_DATA)).Times(1);
	// Act
	m_tespApp->cmdParserAndExcute(WRITE_SUCESS);
}

TEST_F(MockSddFixture, FullWriteSucess) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(_, TEST_DATA)).Times(100);
	// Act
	m_tespApp->cmdParserAndExcute(FULL_WRITE_SUCESS);
}

TEST_F(MockSddFixture, InavlidCmd) {
	// Arrange, Act
	EXPECT_THROW(m_tespApp->cmdParserAndExcute(INVALID_CMD), std::invalid_argument);
}

TEST_F(MockSddFixture, InvalidReadMoreNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(READ_FAIL_MORE_NUM_ARG); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidReadLessNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(READ_FAIL_LESS_NUM_ARG); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidReadInvalidLba) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(READ_FAIL_INVALID_LBA); }, std::invalid_argument);
}

TEST_F(MockSddFixture, InvalidFullReadMoreNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(FULL_READ_FAIL_MORE_NUM_ARG); }, std::invalid_argument);
}

TEST_F(MockSddFixture, InvalidWriteMoreNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(WRITE_FAIL_MORE_NUM_ARG); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidWriteLessNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(WRITE_FAIL_LESS_NUM_ARG); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidWriteSmallLenData) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(WRITE_FAIL_SMALL_LEN_DATA); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidWriteBigLenData) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(WRITE_FAIL_BIC_LEN_DATA); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidWriteNotHexData) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(WRITE_FAIL_NOT_HEX_DATA); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidWriteNotHexCharData) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(WRITE_FAIL_NOT_HEX_CHAR_DATA); }, std::invalid_argument);
}


TEST_F(MockSddFixture, InvalidFullWriteMoreNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(FULL_WRITE_FAIL_MORE_NUM_ARG); }, std::invalid_argument);
}

TEST_F(MockSddFixture, InvalidFullWriteLessNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(FULL_WRITE_FAIL_LESS_NUM_ARG); }, std::invalid_argument);
}

TEST_F(MockSddFixture, InvalidFullWriteInvalidData) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(FULL_WRITE_FAIL_INVALD_DATA); }, std::invalid_argument);
}

TEST_F(MockSddFixture, helpTest) {
	// Arrange, Act
	EXPECT_NO_THROW(m_tespApp->cmdParserAndExcute(HELP_CMD));
}

TEST_F(MockSddFixture, InvalidHelp) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(INVALID_HELP_CMD); }, std::invalid_argument);
}

TEST_F(MockSddFixture, InvalidExit) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(INVALID_EXIT_CMD); }, std::invalid_argument);
}

TEST_F(MockSddFixture, TescScript1) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(_, _)).Times(TEST_SCRIPT1_READ_WRITE_REPEAT_NUM);
	EXPECT_CALL(m_mockSsd, readData(_)).Times(TEST_SCRIPT1_READ_WRITE_REPEAT_NUM);
	// Act
	EXPECT_NO_THROW(m_tespApp->cmdParserAndExcute(TEST_SCRIPT1));
}

TEST_F(MockSddFixture, TescScript1ShortCut) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(_, _)).Times(TEST_SCRIPT1_READ_WRITE_REPEAT_NUM);
	EXPECT_CALL(m_mockSsd, readData(_)).Times(TEST_SCRIPT1_READ_WRITE_REPEAT_NUM);
	// Act
	EXPECT_NO_THROW(m_tespApp->cmdParserAndExcute(TEST_SCRIPT1_SHORT_CUT));
}

TEST_F(MockSddFixture, TescScript2) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(_, _)).Times(TEST_SCRIPT2_READ_WRITE_REPEAT_NUM);
	EXPECT_CALL(m_mockSsd, readData(_)).Times(TEST_SCRIPT2_READ_WRITE_REPEAT_NUM);
	// Act
	EXPECT_NO_THROW(m_tespApp->cmdParserAndExcute(TEST_SCRIPT2));
}

TEST_F(MockSddFixture, TescScript2ShortCut) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(_, _)).Times(TEST_SCRIPT2_READ_WRITE_REPEAT_NUM);
	EXPECT_CALL(m_mockSsd, readData(_)).Times(TEST_SCRIPT2_READ_WRITE_REPEAT_NUM);
	// Act
	EXPECT_NO_THROW(m_tespApp->cmdParserAndExcute(TEST_SCRIPT2_SHORT_CUT));
}

TEST_F(MockSddFixture, TescScript3) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(_, _)).Times(TEST_SCRIPT3_READ_WRITE_REPEAT_NUM);
	EXPECT_CALL(m_mockSsd, readData(_)).Times(TEST_SCRIPT3_READ_WRITE_REPEAT_NUM);
	// Act
	EXPECT_NO_THROW(m_tespApp->cmdParserAndExcute(TEST_SCRIPT3));
}

TEST_F(MockSddFixture, TescScript3ShortCut) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(_, _)).Times(TEST_SCRIPT3_READ_WRITE_REPEAT_NUM);
	EXPECT_CALL(m_mockSsd, readData(_)).Times(TEST_SCRIPT3_READ_WRITE_REPEAT_NUM);
	// Act
	EXPECT_NO_THROW(m_tespApp->cmdParserAndExcute(TEST_SCRIPT3_SHORT_CUT));
}