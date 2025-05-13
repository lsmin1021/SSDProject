#include "full_read_cmd.h"
#include "ssd_interface.h"
#include "iostream"

using std::cout;
void FullReadCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void FullReadCmd::excuteCmd(const vector<string>& tokens) {
    fullRead();
}
void FullReadCmd::helpCmd() const {
    LOG_PRINT("FullReadCmd", "  fullread                 Read all data from LBA addresses (0 ~ 99)\n");
}

void FullReadCmd::fullRead() {
    for (int lba = 0; lba <= MAX_LBA; ++lba)
    {
        m_ssd->readData(std::to_string(lba));
        string log = "[Read] LBA " + std::to_string(lba) + " : " + getReadResult() + "\n";
        LOG_PRINT("FullReadCmd", log);
    }
}
