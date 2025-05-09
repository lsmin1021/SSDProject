#pragma once

#include "ssd_interface.h"

class SsdDriver : public SsdInterface {
public:
	SsdDriver() = default;
	~SsdDriver() override = default;
	void readData(string lba) override {
		// Implementation for reading data from SSD
	}
	void writeData(string lba, string data) override {
		// Implementation for writing data to SSD
	}
};