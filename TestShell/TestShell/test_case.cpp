#pragma once

#include <gmock/gmock.h>
#include "mock_ssd.h"
#include "ssd_driver.h"
#include "test_shell_app.h"

class MockSddFixture : public ::testing::Test {
public:
	MockSsd mockSsd;

	const string TEST_LBA = "0";
	const string TEST_DATA = "0x00000000";
};

TEST_F(MockSddFixture, MockRead) {
	// Arrange
	EXPECT_CALL(mockSsd, readData(TEST_LBA)).Times(1);
	// Act
	mockSsd.readData(TEST_LBA);
}

TEST_F(MockSddFixture, MockWrite) {
	// Arrange
	EXPECT_CALL(mockSsd, writeData(TEST_LBA, TEST_DATA)).Times(1);
	// Act
	mockSsd.writeData(TEST_LBA, TEST_DATA);
}