#pragma once

#include "ssd_interface.h"
#include <gmock/gmock.h>

class MockSsd : public SsdInterface {
public:
	MOCK_METHOD(void, readData, (string lba), (override));
	MOCK_METHOD(void, writeData, (string lba, string data), (override));
};
