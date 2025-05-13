#include "erase_write_aging_ts.h"

void EraseAndWriteAgingTs::checkInvalidCmd(const vector<string>& tokens) const {
    checkNumToken(tokens);
}

void EraseAndWriteAgingTs::excuteCmd(const vector<string>& tokens) {
    int lba = 0;

    m_ssd->eraseData(std::to_string(lba), TEST_ERASE_SIZE);
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
    return lba + TEST_ERASE_SIZE_INT - 1;
}

void EraseAndWriteAgingTs::readAndCompare(const string& addr) const 
{
    m_ssd->readData(addr);
#ifndef _DEBUG
    if (getReadResult().compare(TEST_EXPECTED_VALUE) != 0)
    {
        std::cout << "FAIL\n";
        return;
    }
#endif
}

void EraseAndWriteAgingTs::writeAndErase(const string& addr) const
{
    m_ssd->writeData(addr, TEST_SCRIPT_VALUE);
    m_ssd->writeData(addr, TEST_SCRIPT_OVERWRITE_VALUE);
    m_ssd->eraseData(addr, TEST_ERASE_SIZE);
}
