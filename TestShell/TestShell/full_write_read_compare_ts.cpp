#include "full_write_read_compare_ts.h"
#include "cmd_factory.h"

void FullWriteAndReadCompareTs::checkInvalidTs(const vector<string>& tokens) const {
	checkNumToken(tokens);
}
void FullWriteAndReadCompareTs::excuteTs(const vector<string>& tokens) {
    int lba = 0;

    while (lba <= MAX_LBA) {
        for (int addr = lba; addr < lba + TEST_LBA_STEP; addr++) {
            vector<string> wirteCmd = { "write", std::to_string(addr), TEST_SCRIPT_VALUE };
            executeCmd(wirteCmd);
        }

        for (int addr = lba; addr < lba + TEST_LBA_STEP; addr++) {
            vector<string> readCmd = { "read", std::to_string(addr) };
            executeCmd(readCmd);
#ifndef _DEBUG
            if (cmdObj->getReadResult() != TEST_SCRIPT_VALUE)
            {
                std::cout << "FAIL\n";
                throw FailException();
            }
#endif
        }
        lba += TEST_LBA_STEP;
    }
    std::cout << "PASS\n";
}