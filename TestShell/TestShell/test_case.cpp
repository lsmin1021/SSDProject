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
	const string READ_CMD = "read";
	const string WRITE_CMD = "write";
	const string TEST_LBA = "0";
	const string TEST_DATA = "0x00000000";
	const string INVALID_CMD = "test";

	const string IVALID_TEST_LBA = "100";
	MockSsd m_mockSsd;
	TestShellApp* m_tespApp;
};

TEST_F(MockSddFixture, ReadSuccess) {
	// Arrange
	EXPECT_CALL(m_mockSsd, readData(TEST_LBA)).Times(1);
	// Act
	m_tespApp->readCommand(TEST_LBA);
}
TEST_F(MockSddFixture, ReadFail) {
	// Arrange
	EXPECT_CALL(m_mockSsd, readData(TEST_LBA)).Times(0);
	// Act
	m_tespApp->readCommand(IVALID_TEST_LBA);
}

TEST_F(MockSddFixture, FullReadSuccess) {
	// Arrange
	EXPECT_CALL(m_mockSsd, readData(testing::_)).Times(100);
	// Act
	m_tespApp->fullReadCommand();
}

TEST_F(MockSddFixture, MockWrite) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(TEST_LBA, TEST_DATA)).Times(1);
	// Act
	m_tespApp->writeCommand(TEST_LBA, TEST_DATA);
}

TEST_F(MockSddFixture, InavlidCmd) {
	// Arrange, Act
	EXPECT_THROW(m_tespApp->cmdParserAndExcute(INVALID_CMD), std::invalid_argument);
}