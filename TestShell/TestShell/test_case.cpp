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

	MockSsd m_mockSsd;
	TestShellApp* m_tespApp;
};

TEST_F(MockSddFixture, ReadSuccess) {
	// Arrange
	EXPECT_CALL(m_mockSsd, readData(TEST_LBA)).Times(1);
	// Act
	m_tespApp->readCommand(TEST_LBA);
}

TEST_F(MockSddFixture, MockWrite) {
	// Arrange
	EXPECT_CALL(m_mockSsd, writeData(TEST_LBA, TEST_DATA)).Times(1);
	// Act
	m_tespApp->writeCommand(TEST_LBA, TEST_DATA);
}