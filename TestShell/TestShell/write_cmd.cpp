#include "write_cmd.h"

void WriteCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
    checkLbaArg(tokens[1]);
    checkDataArg(tokens[2]);
}
void WriteCmd::excuteCmd(const vector<string>& tokens) {
	// TODO
   //throu execption
}
void WriteCmd::helpCmd() {}