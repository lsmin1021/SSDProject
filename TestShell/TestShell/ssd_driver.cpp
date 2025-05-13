#include <iostream>
#include "ssd_driver.h"

void SsdDriver::readData(const string& lba) {
	string cmd = READ_CMD + lba;
	int ret = m_executor->run(cmd);
}
void SsdDriver::writeData(const string& lba, const string& data) {
	string cmd = WRITE_CMD + lba + " " + data;
	int ret = m_executor->run(cmd);
 }

void SsdDriver::eraseData(const string& lba, const string& size) {
	string cmd = ERASE_CMD + lba + " " + size;
	int ret = m_executor->run(cmd);
}

void SsdDriver::eraseDataRange(const string& StartLba, const string& endLba) {

}