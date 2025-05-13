#include "exit_cmd.h"
#include "iostream"

using std::cout;
void ExitCmd::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void ExitCmd::excuteCmd(const vector<string>& tokens){
	throw ExitException();
}
void ExitCmd::helpCmd() const {
	LOG_PRINT("ExitCmd", "  exit                     Exit the shell\n");
}