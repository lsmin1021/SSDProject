#include "exit_cmd.h"
#include "iostream"
#include "msg_handler.h"

using std::cout;
void ExitCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void ExitCmd::excuteCmd(const vector<string>& tokens){
	throw ExitException();
}
void ExitCmd::helpCmd() const {
	MSG_PRINT("  exit                     Exit the shell\n");
}