#include "erase_write_aging_ts.h"

void EraseAndWriteAgingTs::checkInvalidCmd(const vector<string>& tokens) const {
    checkNumToken(tokens);
}

void EraseAndWriteAgingTs::excuteCmd(const vector<string>& tokens) {
    int lba = 0;

    m_ssd->eraseData(std::to_string(lba), TEST_ERASE_SIZE);
    lba += TEST_ERASE_SIZE_INT - 1;

    for (int iter = 0; iter < TEST_MAX_ITERATE; iter++) {
        for(lba = 2; lba < MAX_LBA; lba+= TEST_ERASE_SIZE_INT) {
            string addr = std::to_string(lba);
            eraseAndReadAssert(addr);
        }
    }
    
    std::cout << "PASS\n";
}

void EraseAndWriteAgingTs::eraseAndReadAssert(const string& addr) const
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

void EraseAndWriteAgingTs::readAndCompare(const string& addr) const 
{
    m_ssd->readData(addr);
#ifndef _DEBUG
    if (m_ssd->getReadResult().compare(TEST_EXPECTED_VALUE) != 0)
    {
        std::cout << "FAIL";
        throw FailException();
    }
#endif
}

void EraseAndWriteAgingTs::writeAndErase(const string& addr) const
{
    m_ssd->writeData(addr, TEST_SCRIPT_VALUE);
    m_ssd->writeData(addr, TEST_SCRIPT_OVERWRITE_VALUE);
    m_ssd->eraseData(addr, TEST_ERASE_SIZE);
}
