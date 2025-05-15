#include "full_read_cmd.h"
#include "ssd_interface.h"
#include "msg_handler.h"
#include "logger.h"

void FullReadCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void FullReadCmd::excuteCmd(const vector<string>& tokens) {
    fullRead();
}
void FullReadCmd::helpCmd() const {
    std::stringstream formatted;
    formatted << std::left << std::setw(30) << "  fullread" << "Read all data from LBA addresses (0 ~ 99)\n\n";
    MSG_PRINT(formatted.str());
}

void FullReadCmd::fullRead() {
    for (int lba = 0; lba <= MAX_LBA; ++lba)
    {
        m_ssd->readData(std::to_string(lba));
        MSG_PRINT("[Read] LBA " + std::to_string(lba) + " : " + getReadResult() + "\n");
    }
}
