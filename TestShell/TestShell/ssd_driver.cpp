#include <iostream>
#include "ssd_driver.h"

void SsdDriver::readData(string lba) {
	string cmd = READ_CMD + lba;
	int ret = system(cmd.c_str());
}
void SsdDriver::writeData(string lba, string data) {
	string cmd = WRITE_CMD + lba + " " + data;
	int ret = system(cmd.c_str());
 }