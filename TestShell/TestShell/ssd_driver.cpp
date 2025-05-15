#include <iostream>
#include "ssd_driver.h"

void SsdDriver::readData(const string& lba) {
	string cmd = READ_CMD + lba;
	int ret = system(cmd.c_str());
	LOG_PRINT("SsdDriver", cmd + "\n");
}
void SsdDriver::writeData(const string& lba, const string& data) {
	string cmd = WRITE_CMD + lba + " " + data;
	int ret = system(cmd.c_str());
	LOG_PRINT("SsdDriver", cmd + "\n");
 }

void SsdDriver::eraseData(const string& lba, const string& size) {
	string cmd = ERASE_CMD + lba + " " + size;
	int ret = system(cmd.c_str());
	LOG_PRINT("SsdDriver", cmd + "\n");
}

void SsdDriver::flush(void) {
	string cmd = FLUSH_CMD;
	int ret = system(cmd.c_str());
	LOG_PRINT("SsdDriver", cmd + "\n");
}

string SsdDriver::getReadResult() {
	std::ifstream resultHandler(FILE_NAME);
	string result = "";

	if(resultHandler.is_open()) {
		getline(resultHandler, result);
		LOG_PRINT("SsdDriver", result + "\n");
	}
	else {
		LOG_PRINT("SsdDriver", "ssd_output.txt can`t be opend\n");
	}

	return result;
}