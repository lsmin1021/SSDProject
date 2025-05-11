#pragma once

#include <gmock/gmock.h>
#include "mock_ssd.h"
#include "ssd_driver.h"
#include "test_shell_app.h"

class MockSddFixture : public ::testing::Test {
protected:
	void SetUp() {
		m_tespApp = new TestShellApp(&m_mockSsd);
	}

public:
	const string TEST_LBA = "0";
	const string TEST_DATA = "0x00000000";
	const string INVALID_CMD = "test";
	const string READ_SUCESS = "read 0";
	const string READ_FALL_LESS_NUM_ARG = "read";
	const string READ_FALL_MORE_NUM_ARG = "read 0 1";
	const string READ_FALL_INVALE_LAB = "read 100";
	const string FULL_READ_SUCESS = "fullread";
	const string WRITE_SUCESS = "write 0 0x00000000";
	const string FULL_WRITE_SUCESS = "fullwrite 0x00000000";

	MockSsd m_mockSsd;
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
	EXPECT_CALL(m_mockSsd, readData(testing::_)).Times(100);
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
	EXPECT_CALL(m_mockSsd, writeData(testing::_, TEST_DATA)).Times(100);
	// Act
	m_tespApp->cmdParserAndExcute(FULL_WRITE_SUCESS);
}

TEST_F(MockSddFixture, InavlidCmd) {
	// Arrange, Act
	EXPECT_THROW(m_tespApp->cmdParserAndExcute(INVALID_CMD), std::invalid_argument);
}

TEST_F(MockSddFixture, InvalidReadMoreNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(READ_FALL_MORE_NUM_ARG); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidReadLessNumAra) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(READ_FALL_LESS_NUM_ARG); }, std::invalid_argument);
}
TEST_F(MockSddFixture, InvalidReadInvalidLAB) {
	EXPECT_THROW({ m_tespApp->cmdParserAndExcute(READ_FALL_INVALE_LAB); }, std::invalid_argument);
}