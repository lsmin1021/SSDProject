#include "partial_lba_write_ts.h"
#include "cmd_factory.h"
void PartialLbaWriteTs::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}

void PartialLbaWriteTs::excuteCmd(const vector<string>& tokens) {
    int iter = 0;
    vector<string> test_addr = { "4", "0", "3", "1", "2" };

    while (iter < TEST_SCRIPT2_REPEAT_NUM) {
        for (auto addr : test_addr) {
            vector<string> wirteCmd = { "write", addr, TEST_SCRIPT_VALUE };
            // LDY TODO
            //CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(wirteCmd[0]);
            //cmdObj->excuteCmd(wirteCmd);
        }


        for (int addr = 0; addr < TEST_SCRIPT2_LBA_STEP; addr++) {
            vector<string> readCmd = { "read", std::to_string(addr) };
            // LDY TODO
            //CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(readCmd[0]);
            //cmdObj->excuteCmd(readCmd);
#ifndef _DEBUG
            if (cmdObj->getReadResult().compare(TEST_SCRIPT_VALUE) != 0)
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
