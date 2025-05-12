#include "write_cmd.h"
#include "ssd_driver.h"

void WriteCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
    checkLbaArg(tokens[1]);
    checkDataArg(tokens[2]);
}
void WriteCmd::excuteCmd(const vector<string>& tokens) {
    string lba = tokens[1];
    string value = tokens[2];
    write(lba, value);
}
void WriteCmd::helpCmd() {}

void WriteCmd::write(const string& lba, const string& value) {
    m_ssd->writeData(lba, value);
}