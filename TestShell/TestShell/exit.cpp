#include "exit_cmd.h"
#include "iostream"

using std::cout;
void ExitCmd::checkInvalidCmd(const vector<string>& tokens) {
	checkNumToken(tokens);
}
void ExitCmd::excuteCmd(const vector<string>& tokens){
	throw ExitException();
}
void ExitCmd::helpCmd() {
	cout << "  exit                     Exit the shell\n";
}