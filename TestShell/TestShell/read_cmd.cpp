#include "read_cmd.h"
#include "ssd_driver.h"
#include "msg_handler.h"
#include "logger.h"

void ReadCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
	checkLbaArg(tokens[1]);
}
void ReadCmd::excuteCmd(const vector<string>& tokens) {
	string lba = tokens[1];
	read(lba);
}
void ReadCmd::helpCmd() const {
	std::stringstream formatted;
	formatted << std::left << std::setw(30) << "  read <LBA>" << "Read data from the specified LBA\n";
	MSG_PRINT(formatted.str());
}

void ReadCmd::read(const string& lbaString) {
	m_ssd->readData(lbaString);
	MSG_PRINT("[Read] LBA " + lbaString + " : " + getReadResult() + "\n");
}