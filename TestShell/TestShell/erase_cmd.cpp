#include "erase_cmd.h"
#include "ssd_interface.h"
#include "iostream"

using std::cout;
void EraseCmd::checkInvalidCmd(const vector<string>& tokens) const {
    checkNumToken(tokens);
}
void EraseCmd::excuteCmd(const vector<string>& tokens) {
    
}
void EraseCmd::helpCmd() const {
    cout << "  fullread                 Read all data from LBA addresses (0 ~ 99)\n";
}
