#include "full_write_cmd.h"

void FullWriteCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
	checkDataArg(tokens[1]);
}
void FullWriteCmd::excuteCmd(const vector<string>& tokens) {
	// TODO
   //throu execption
}
void FullWriteCmd::helpCmd() {}