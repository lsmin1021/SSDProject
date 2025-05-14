#include "erase_cmd.h"
#include "ssd_interface.h"
#include "iostream"
#include "msg_handler.h"

void EraseCmd::checkInvalidCmd(const vector<string>& tokens) const {
    checkNumToken(tokens);
    string lbaString = tokens[1];
    string sizeString = tokens[2];
    checkLbaArg(lbaString);
    checkSizeArg(sizeString);
}
void EraseCmd::excuteCmd(const vector<string>& tokens) {
    string lbaString = tokens[1];
    string sizeString = tokens[2];
    vector<EraseArg> args = makeFitSizeForSsd(lbaString, sizeString);
    for (auto arg : args) {
        m_ssd->eraseData(arg.lbaString, arg.sizeString);
    }
}
void EraseCmd::helpCmd() const {
    MSG_PRINT("  erase <LBA>  <SIZE>       Erase 4-byte DATAs of SIZE from logical block address (LBA)\n");
}

void EraseCmd::checkSizeArg(const string& sizeString) const {
    std::size_t errorPos = 0;
    int size = std::stoi(sizeString, &errorPos);
    if (isValidSizeString(sizeString, errorPos)) return;
    throw std::invalid_argument("Usage: decial size");
}

vector<EraseArg> EraseCmd::makeFitSizeForSsd(const string& lbaString, const string& sizeSring) {
    vector<EraseArg> result;
    EraseArg eraseArg;
    int startLba = std::stoi(lbaString);
    int eraseSize = std::stoi(sizeSring);

    if (eraseSize < 0) {
        eraseSize *= -1;
        startLba = startLba - eraseSize + 1;
        if (startLba < MIN_LBA) {
            eraseSize += startLba;
            startLba = MIN_LBA;
        }
    }

    while(eraseSize > 0 && startLba <= MAX_LBA){
        int resize = 0;
        if (eraseSize > MAX_SIZE_FOR_SSD) resize = MAX_SIZE_FOR_SSD;
        else resize = eraseSize;

        eraseArg.lbaString = std::to_string(startLba);
        eraseArg.sizeString = std::to_string(resize);
        result.push_back(eraseArg);

        startLba += resize;
        eraseSize -= resize;
    }
    return result;
}