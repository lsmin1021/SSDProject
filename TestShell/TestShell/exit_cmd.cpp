#include "exit_cmd.h"
#include "msg_handler.h"
#include "logger.h"

void ExitCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void ExitCmd::excuteCmd(const vector<string>& tokens){
	throw ExitException();
}
void ExitCmd::helpCmd() const {
	MSG_PRINT("  exit                     Exit the shell\n");
}