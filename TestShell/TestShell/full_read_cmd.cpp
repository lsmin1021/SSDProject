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
    cout << "  fullread                 Read all data from LBA addresses (0 ~ 99)\n";
}

void FullReadCmd::fullRead() {
    for (int lba = 0; lba <= MAX_LBA; ++lba)
    {
        m_ssd->readData(std::to_string(lba));
        cout << "[Read] LBA " << std::to_string(lba) << " : " << getReadResult() << std::endl;
    }
}
