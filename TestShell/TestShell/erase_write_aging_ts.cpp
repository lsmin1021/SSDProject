#include "erase_write_aging_ts.h"
#include "cmd_factory.h"
void EraseAndWriteAgingTs::checkInvalidCmd(const vector<string>& tokens) const {
    checkNumToken(tokens);
}

void EraseAndWriteAgingTs::excuteCmd(const vector<string>& tokens) {
    int lba = 0;

    vector<string> eraseCmd = { "erase", std::to_string(lba), TEST_ERASE_SIZE };
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(eraseCmd[0]);
    cmdObj->excuteCmd(eraseCmd);

    lba += TEST_ERASE_SIZE_INT - 1;
    for (int iter = 0; iter < TEST_MAX_ITERATE; iter++) {
        string addr = std::to_string(lba);
        lba = eraseAndReadAssert(addr, lba);
        lba = eraseAndReadAssert(addr, lba);
        lba = eraseAndReadAssert(addr, lba);
    }   
    
    std::cout << "PASS\n";
}

int EraseAndWriteAgingTs::eraseAndReadAssert(const string& addr, int lba) const
{
    writeAndErase(addr);
    readAndCompare(addr);
    return nextLbaAddr(lba);
}

int EraseAndWriteAgingTs::nextLbaAddr(int lba) const
{
    int result = lba + TEST_ERASE_SIZE_INT - 1;
    if (result > MAX_LBA) return result - MAX_LBA - 1;
    return result;
}

void EraseAndWriteAgingTs::readAndCompare(const string& addr) const 
{
    vector<string> readCmd = { "read", addr };
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(readCmd[0]);
    cmdObj->excuteCmd(readCmd);
#ifndef _DEBUG
    if (getReadResult().compare(TEST_EXPECTED_VALUE) != 0)
    {
        std::cout << "FAIL";
        throw FailException();
    }
#endif
}

void EraseAndWriteAgingTs::writeAndErase(const string& addr) const
{
    vector<string> wirteCmd = { "write", addr, TEST_SCRIPT_VALUE };
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(wirteCmd[0]);
    cmdObj->excuteCmd(wirteCmd);

    wirteCmd = { "write", addr, TEST_SCRIPT_OVERWRITE_VALUE };
    cmdObj->excuteCmd(wirteCmd);

    vector<string> eraseCmd = { "erase", addr, TEST_ERASE_SIZE };
    cmdObj = CmdFactory::getInstance().getCmd(eraseCmd[0]);
    cmdObj->excuteCmd(eraseCmd);
}
