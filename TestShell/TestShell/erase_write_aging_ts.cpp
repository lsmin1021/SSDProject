#include "erase_write_aging_ts.h"
#include "cmd_factory.h"

void EraseAndWriteAgingTs::checkInvalidTs(const vector<string>& tokens) const {
    checkNumToken(tokens);
}

void EraseAndWriteAgingTs::excuteTs(const vector<string>& tokens) {
    int lba = 0;

    vector<string> eraseCmd = { "erase", std::to_string(lba), TEST_ERASE_SIZE };
    executeCmd(eraseCmd);
 
    lba += TEST_ERASE_SIZE_INT - 1;

    for (int iter = 0; iter < TEST_MAX_ITERATE; iter++) {
        for(lba = 2; lba < MAX_LBA; lba+= TEST_ERASE_SIZE_INT) {
            string addr = std::to_string(lba);
            eraseAndReadAssert(addr);
        }
    }
    
    return;
}

void EraseAndWriteAgingTs::eraseAndReadAssert(const string& addr)
{
    writeAndErase(addr);
    readAndCompare(addr);
}

int EraseAndWriteAgingTs::nextLbaAddr(int lba) const
{
    int result = lba + TEST_ERASE_SIZE_INT - 1;
    if (result > MAX_LBA) return result - MAX_LBA - 1;
    return result;
}

void EraseAndWriteAgingTs::readAndCompare(const string& addr) 
{
    vector<string> readCmd = { "read", addr };
#ifdef _DEBUG
    executeCmd(readCmd);
#else
    executeCmd(readCmd, TEST_EXPECTED_VALUE);
#endif
}

void EraseAndWriteAgingTs::writeAndErase(const string& addr)
{
    vector<string> wirteCmd = { "write", addr, TEST_SCRIPT_VALUE };
    executeCmd(wirteCmd);

    wirteCmd = { "write", addr, TEST_SCRIPT_OVERWRITE_VALUE };
    executeCmd(wirteCmd);

    vector<string> eraseCmd = { "erase", addr, TEST_ERASE_SIZE };
    executeCmd(eraseCmd);
}
