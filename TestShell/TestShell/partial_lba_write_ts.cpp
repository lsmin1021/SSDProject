#include "partial_lba_write_ts.h"

void PartialLbaWriteTs::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}

void PartialLbaWriteTs::excuteCmd(const vector<string>& tokens) {
    int iter = 0;
    vector<string> test_addr = { "4", "0", "3", "1", "2" };

    while (iter < TEST_SCRIPT2_REPEAT_NUM) {
        for (auto addr : test_addr)
            m_ssd->writeData(addr, TEST_SCRIPT_VALUE);


        for (int addr = 0; addr < TEST_SCRIPT2_LBA_STEP; addr++) {
            m_ssd->readData(std::to_string(addr));
#ifndef _DEBUG
            if (getReadResult().compare(TEST_SCRIPT_VALUE) != 0)
            {
                std::cout << "FAIL\n";
                throw FailException();
            }
#endif
        }
        iter++;
    }

    std::cout << "PASS\n";
}
