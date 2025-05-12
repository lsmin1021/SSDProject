#include "exit_cmd.h"

void ExitCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
}
void ExitCmd::excuteCmd(const vector<string>& tokens){
	throw ExitException();
}
void ExitCmd::helpCmd() {}