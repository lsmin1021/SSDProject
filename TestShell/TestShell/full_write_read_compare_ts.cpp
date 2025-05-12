#include "full_write_read_compare_ts.h"

void FullWriteAndReadCompareTs::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void FullWriteAndReadCompareTs::excuteCmd(const vector<string>& tokens) {
    fullWirte();
    fullRead();
    std::cout << "PASS\n";
}

void FullWriteAndReadCompareTs::fullWirte() {
    int lba = 0;

    while (lba <= MAX_LBA) {
        for (int addr = lba; addr < lba + TEST_SCRIPT1_LBA_STEP; addr++) {
            m_ssd->writeData(std::to_string(addr), TEST_SCRIPT_VALUE);
        }
        lba += TEST_SCRIPT1_LBA_STEP;
    }
}
void FullWriteAndReadCompareTs::fullRead() {
    int lba = 0;
    while (lba <= MAX_LBA) {
        for (int addr = lba; addr < lba + TEST_SCRIPT1_LBA_STEP; addr++) {
            m_ssd->readData(std::to_string(addr));
#ifndef _DEBUG
            if (getReadResult() != TEST_SCRIPT_VALUE)
            {
                std::cout << "FAIL\n";
                return;
            }
#endif
        }
        lba += TEST_SCRIPT1_LBA_STEP;
    }
}