#include "write_read_aging_ts.h"
#include "cmd_factory.h"

void WriteReadAging::checkInvalidCmd(const vector<string>& tokens) const {
	checkNumToken(tokens);
}

string WriteReadAging::generateRandomHexString() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

    uint32_t randomValue = dist(gen);

    std::stringstream ss;
    ss << "0x" << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << randomValue;
    return ss.str();
}

void WriteReadAging::excuteCmd(const vector<string>& tokens) {
    string valueForStartLba = "";
    string valueForEndLba = "";

    for (int iter = 0; iter < TEST_MAX_ITERATE; iter++) {
        valueForStartLba = generateRandomHexString();
        valueForEndLba = generateRandomHexString();

        vector<string> writeCmd = { "write", START_LBA, valueForStartLba };
        CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(writeCmd[0]);
        cmdObj->excuteCmd(writeCmd);

        writeCmd = { "write", END_LBA, valueForEndLba };
        cmdObj->excuteCmd(writeCmd);

        vector<string> readCmd = { "read", START_LBA };
        CmdInterface* cmdObj2 = CmdFactory::getInstance().getCmd(readCmd[0]);
        cmdObj2->excuteCmd(readCmd);

#ifndef _DEBUG
        if (getReadResult().compare(valueForStartLba) != 0)
        {
            std::cout << "FAIL\n";
            throw FailException();
        }
#endif
        readCmd = { "read", END_LBA };
        cmdObj2->excuteCmd(readCmd);
#ifndef _DEBUG
        if (getReadResult().compare(valueForEndLba) != 0)
        {
            std::cout << "FAIL\n";
            throw FailException();
        }
#endif
    }

    std::cout << "PASS\n";
}