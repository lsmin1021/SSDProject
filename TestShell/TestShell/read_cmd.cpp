#include "read_cmd.h"
#include "ssd_driver.h"

void ReadCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
	checkLbaArg(tokens[1]);
}
void ReadCmd::excuteCmd(const vector<string>& tokens) {
	string lba = tokens[1];
	read(lba);
}
void ReadCmd::helpCmd() {}

void ReadCmd::read(const string& lbaString) {
	m_ssd->readData(lbaString);
}