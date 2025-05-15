#include "flush_cmd.h"
#include "ssd_interface.h"
#include "msg_handler.h"
#include "logger.h"

void FlushCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}

void FlushCmd::excuteCmd(const vector<string>& tokens) {
	flush();
}

void FlushCmd::helpCmd() const {
	MSG_PRINT("  flush                     Flush the buffered commands to Nand\n");
}

void FlushCmd::flush() {
	m_ssd->flush();
	MSG_PRINT("[Flush] DONE\n");
}