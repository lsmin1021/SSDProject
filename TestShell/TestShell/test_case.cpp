#pragma once

#include <gmock/gmock.h>
#include "mock_ssd.h"
#include "ssd_driver.h"
#include "test_shell_app.h"

TEST(TestShell, MockRead) {
	// Arrange
	MockSsd mockSsd;
	EXPECT_CALL(mockSsd, readData("0")).Times(1);
	// Act
	mockSsd.readData("0");
}

TEST(TestShell, MockWrite) {
	// Arrange
	MockSsd mockSsd;
	EXPECT_CALL(mockSsd, writeData("0", "0x00000000")).Times(1);
	// Act
	mockSsd.writeData("0", "0x00000000");
}