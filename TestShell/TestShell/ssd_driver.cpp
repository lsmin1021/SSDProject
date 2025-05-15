#include <iostream>
#include "ssd_driver.h"

void SsdDriver::readData(const string& lba) {
	string cmd = READ_CMD + lba;
	int ret = system(cmd.c_str());
	LOG_PRINT("SsdDriver", cmd + "\n");
	LOG_PRINT("SsdDriver", "read result : " + getReadResult() + "\n");

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
	std::ifstream file("ssd_output.txt");

	if (!file.is_open()) {
		return "";
	}

	string result;
	getline(file, result);
	file.close();

	return result;
}