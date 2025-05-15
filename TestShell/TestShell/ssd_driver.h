#pragma once
#include <cstdlib> 
#include <filesystem>
#include "ssd_interface.h"
#include "logger.h"

class SsdDriver : public SsdInterface {
public:
	SsdDriver() = default;
	~SsdDriver() = default;
	void readData(const string& lba) override;
	void writeData(const string& lba, const string& data) override;
	void eraseData(const string& lba, const string& size) override;
	void flush(void) override;
	

private:
	const string FILE_NAME = "ssd_output.txt";
	const string WRITE_CMD = "SSD W ";
	const string READ_CMD = "SSD R ";
	const string ERASE_CMD = "SSD E ";
	const string FLUSH_CMD = "SSD F";
	string getReadResult() override;
};