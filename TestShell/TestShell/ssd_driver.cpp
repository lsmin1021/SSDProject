#include <iostream>
#include "ssd_driver.h"

void SsdDriver::readData(const string& lba) {
	string cmd = READ_CMD + lba;
	int ret = system(cmd.c_str());
}
void SsdDriver::writeData(const string& lba, const string& data) {
	string cmd = WRITE_CMD + lba + " " + data;
	int ret = system(cmd.c_str());
 }