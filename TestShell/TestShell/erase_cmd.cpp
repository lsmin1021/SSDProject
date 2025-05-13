#include "erase_cmd.h"
#include "ssd_interface.h"
#include "iostream"

using std::cout;

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
    cout << "  erase <LBA>  <SIZE>       Erase 4-byte DATAs of SIZE from logical block address (LBA)\n";
}

void EraseCmd::checkSizeArg(const string& sizeString) const {
    std::size_t errorPos = 0;
    int size = std::stoi(sizeString, &errorPos);
    if (isValidSizeString(sizeString, errorPos))
    {
        if (size >= 0) {
            return;
        }
        throw std::invalid_argument("Usage: size >= 0");
    }
    throw std::invalid_argument("Usage: decial size");
}

vector<EraseArg> EraseCmd::makeFitSizeForSsd(const string& lbaString, const string& sizeSring) {
    vector<EraseArg> result;
    EraseArg eraseArg;
    int resize = 0;
    int lba = std::stoi(lbaString);
    int size = std::stoi(sizeSring);
    while(size > 0 && lba <= MAX_LBA){

        if (size > MAX_SIZE_FOR_SSD) resize = MAX_SIZE_FOR_SSD;
        else resize = size;

        eraseArg.lbaString = std::to_string(lba);
        eraseArg.sizeString = std::to_string(resize);
        result.push_back(eraseArg);

        lba += resize;
        size -= resize;
    }
    return result;
}