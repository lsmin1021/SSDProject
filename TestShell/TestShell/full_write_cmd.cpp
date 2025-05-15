#include "full_write_cmd.h"
#include "ssd_interface.h"
#include "msg_handler.h"
#include "logger.h"

void FullWriteCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
    string dataString = tokens[1];
	checkDataArg(dataString);
}
void FullWriteCmd::excuteCmd(const vector<string>& tokens) {
    string dataString = tokens[1];
    fullWrite(dataString);
}
void FullWriteCmd::helpCmd() const {
    MSG_PRINT("  fullwrite <DATA>               Write 4-byte DATA to all LBA addresses(0 ~ 99)\n");
}

void FullWriteCmd::fullWrite(const string& value) {
    for (int lba = 0; lba <= MAX_LBA; ++lba) {
		m_ssd->writeData(std::to_string(lba), value);
    }
    MSG_PRINT("[FullWrite] DONE\n");
}

