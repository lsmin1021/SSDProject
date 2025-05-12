#pragma once
#include <cstdlib>  
#include "ssd_interface.h"

class SsdDriver : public SsdInterface {
public:
	SsdDriver() = default;
	~SsdDriver() override = default;
	void readData(string lba) override;
	void writeData(string lba, string data) override;

private:
	const string WRITE_CMD = "SSD W ";
	const string READ_CMD = "SSD R ";
};