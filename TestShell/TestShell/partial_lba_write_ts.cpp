#include "partial_lba_write_ts.h"
#include "cmd_factory.h"

void PartialLbaWriteTs::checkInvalidTs(const vector<string>& tokens) const {
	checkNumToken(tokens);
}

void PartialLbaWriteTs::excuteTs(const vector<string>& tokens) {
    int iter = 0;
    vector<string> test_addr = { "4", "0", "3", "1", "2" };

    while (iter < TEST_SCRIPT2_REPEAT_NUM) {
        for (auto addr : test_addr) {
            vector<string> wirteCmd = { "write", addr, TEST_SCRIPT_VALUE };
            executeCmd(wirteCmd);
        }


        for (int addr = 0; addr < TEST_SCRIPT2_LBA_STEP; addr++) {
            vector<string> readCmd = { "read", std::to_string(addr) };
#ifdef _DEBUG
            executeCmd(readCmd);
#else
            executeCmd(readCmd,TEST_SCRIPT_VALUE);
#endif
        }
        iter++;
    }

    return;
}
