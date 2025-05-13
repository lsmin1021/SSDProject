#include "erase_range_cmd.h"
#include "ssd_interface.h"
#include "iostream"

using std::cout;
void EraseRangeCmd::checkInvalidCmd(const vector<string>& tokens) const {
    checkNumToken(tokens);
    string startLbaString = tokens[1];
    string endLbaString = tokens[2];
    checkLbaArg(startLbaString);
    checkLbaArg(endLbaString);
}

void EraseRangeCmd::excuteCmd(const vector<string>& tokens) {  
   string startLbaString = tokens[1];  
   string endLbaString = tokens[2];  
   int startLba = std::stoi(startLbaString);  
   int endLba = std::stoi(endLbaString);  

   string sizeString = std::to_string(endLba - startLba + 1);  
   vector<string> newTokens;
   newTokens.push_back(getName()[0]);
   newTokens.push_back(startLbaString);  
   newTokens.push_back(sizeString);  

   EraseCmd::excuteCmd(newTokens);  
}
void EraseRangeCmd::helpCmd() const {
    cout << "  erase <START LBA>  <END LBA>       Erase 4-byte DATAs from START LBA to END LBA\n";
}
