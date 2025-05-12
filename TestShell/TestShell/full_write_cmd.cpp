#include "full_write_cmd.h"
#include "ssd_interface.h"
#include "iostream"

using std::cout;
void FullWriteCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
	checkDataArg(tokens[1]);
}
void FullWriteCmd::excuteCmd(const vector<string>& tokens) {
    string value = tokens[1];
    fullWrite(value);
}
void FullWriteCmd::helpCmd() {
    cout << "  fullwrite                Write default data to all LBA addresses (0 ~ 99)\n";
}

void FullWriteCmd::fullWrite(const string& value) {
    for (int lba = 0; lba <= MAX_LBA; ++lba) {
		m_ssd->writeData(std::to_string(lba), value);
    }
}

