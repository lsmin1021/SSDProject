#include "read_cmd.h"

void ReadCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
	checkLbaArg(tokens[1]);
}
void ReadCmd::excuteCmd(const vector<string>& tokens) {
	// TODO
   //throu execption
}
void ReadCmd::helpCmd() {}