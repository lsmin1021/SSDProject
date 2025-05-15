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
    std::stringstream formatted;
    formatted << std::left << std::setw(30) << "  fullwrite <DATA>" << "Write 4-byte DATA to all LBA addresses(0 ~ 99)\n";
    MSG_PRINT(formatted.str());
}

void FullWriteCmd::fullWrite(const string& value) {
    for (int lba = 0; lba <= MAX_LBA; ++lba) {
		m_ssd->writeData(std::to_string(lba), value);
    }
    MSG_PRINT("[FullWrite] DONE\n");
}

