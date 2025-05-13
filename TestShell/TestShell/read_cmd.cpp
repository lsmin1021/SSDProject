#include "read_cmd.h"
#include "ssd_driver.h"
#include "iostream"

using std::cout;
void ReadCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
	checkLbaArg(tokens[1]);
}
void ReadCmd::excuteCmd(const vector<string>& tokens) {
	string lba = tokens[1];
	read(lba);
}
void ReadCmd::helpCmd() const {
	cout << "  read <LBA>               Read data from the specified LBA\n";
}

void ReadCmd::read(const string& lbaString) {
	m_ssd->readData(lbaString);
}