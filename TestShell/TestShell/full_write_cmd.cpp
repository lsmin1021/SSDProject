#include "full_write_cmd.h"
#include "ssd_interface.h"

void FullWriteCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
	checkDataArg(tokens[1]);
}
void FullWriteCmd::excuteCmd(const vector<string>& tokens) {
    string value = tokens[1];
    fullWrite(value);
}
void FullWriteCmd::helpCmd() {}

void FullWriteCmd::fullWrite(const string& value) {
    for (int lba = 0; lba <= MAX_LBA; ++lba) {
		m_ssd->writeData(std::to_string(lba), value);
    }
}

