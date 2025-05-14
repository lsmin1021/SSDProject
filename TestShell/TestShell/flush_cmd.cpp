#include "flush_cmd.h"
#include "ssd_interface.h"
#include "iostream"

using std::cout;

void FlushCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}

void FlushCmd::excuteCmd(const vector<string>& tokens) {
	m_ssd->flush();
}

void FlushCmd::helpCmd() const {
	cout << "  flush                     Flush the buffered commands to Nand\n";
}