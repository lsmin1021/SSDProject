#include "full_read_cmd.h"
#include "ssd_interface.h"

void FullReadCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
}
void FullReadCmd::excuteCmd(const vector<string>& tokens) {
    fullRead();
}
void FullReadCmd::helpCmd() {}

void FullReadCmd::fullRead() {
    for (int lba = 0; lba <= MAX_LBA; ++lba)
    {
        m_ssd->readData(std::to_string(lba));
    }
}
