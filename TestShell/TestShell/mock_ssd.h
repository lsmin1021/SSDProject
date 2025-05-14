#pragma once

#include "ssd_interface.h"
#include <gmock/gmock.h>

class MockSsd : public SsdInterface {
public:
	MOCK_METHOD(void, readData, (const string& lba), (override));
	MOCK_METHOD(void, writeData, (const string& lba, const string& data), (override));
	MOCK_METHOD(void, eraseData, (const string& lba, const string& size), (override));
	MOCK_METHOD(void, flush, (), (override));
	MOCK_METHOD(string, getReadResult, (), (override));
};
