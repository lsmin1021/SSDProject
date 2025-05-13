#include "write_cmd.h"
#include "ssd_driver.h"
#include "iostream"

using std::cout;
void WriteCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
    checkLbaArg(tokens[1]);
    checkDataArg(tokens[2]);
}
void WriteCmd::excuteCmd(const vector<string>& tokens) {
    string lba = tokens[1];
    string value = tokens[2];
    write(lba, value);
}
void WriteCmd::helpCmd() const {
    cout << "  write <LBA> <DATA>       Write 4-byte DATA to logical block address (LBA)\n";
}

void WriteCmd::write(const string& lba, const string& value) {
    m_ssd->writeData(lba, value);
}