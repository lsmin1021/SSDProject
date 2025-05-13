#include "erase_write_aging_ts.h"

void EraseAndWriteAgingTs::checkInvalidCmd(const vector<string>& tokens) const {
    checkNumToken(tokens);
}

void EraseAndWriteAgingTs::excuteCmd(const vector<string>& tokens) {
    int lba = 0;

    m_ssd->eraseData(std::to_string(lba), TEST_ERASE_SIZE);
    lba += TEST_ERASE_SIZE_INT - 1;
    for (int iter = 0; iter < TEST_MAX_ITERATE; iter++) {
        // 2번LBA Write
        // 2번LBA OverWrite
        // 2 ~4번 LBA 삭제
        string addr = std::to_string(lba);
        m_ssd->writeData(addr, TEST_SCRIPT_VALUE);
        m_ssd->writeData(addr, TEST_SCRIPT_OVERWRITE_VALUE);
        m_ssd->eraseData(addr, TEST_ERASE_SIZE);
        lba += TEST_ERASE_SIZE_INT - 1;

        m_ssd->readData(addr);
#ifndef _DEBUG
        if (getReadResult().compare(TEST_EXPECTED_VALUE) != 0)
        {
            std::cout << "FAIL\n";
            return;
        }
#endif

        m_ssd->writeData(addr, TEST_SCRIPT_VALUE);
        m_ssd->writeData(addr, TEST_SCRIPT_OVERWRITE_VALUE);
        m_ssd->eraseData(addr, TEST_ERASE_SIZE);
        lba += TEST_ERASE_SIZE_INT - 1;

        m_ssd->readData(addr);
#ifndef _DEBUG
        if (getReadResult().compare(TEST_EXPECTED_VALUE) != 0)
        {
            std::cout << "FAIL\n";
            return;
        }
#endif

        m_ssd->writeData(addr, TEST_SCRIPT_VALUE);
        m_ssd->writeData(addr, TEST_SCRIPT_OVERWRITE_VALUE);
        m_ssd->eraseData(addr, TEST_ERASE_SIZE);
        lba += TEST_ERASE_SIZE_INT - 1;

        m_ssd->readData(addr);
#ifndef _DEBUG
        if (getReadResult().compare(TEST_EXPECTED_VALUE) != 0)
        {
            std::cout << "FAIL\n";
            return;
        }
#endif
    }   
    
    std::cout << "PASS\n";
}