#include "flush_cmd.h"
#include "ssd_interface.h"
#include "iostream"
#include "msg_handler.h"

void FlushCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}

void FlushCmd::excuteCmd(const vector<string>& tokens) {
	m_ssd->flush();
}

void FlushCmd::helpCmd() const {
	MSG_PRINT("  flush                     Flush the buffered commands to Nand\n");
}