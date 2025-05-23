#include "write_read_aging_ts.h"

TsInterface* TsInterface::getInstance(AppCb* appCb) {
    static WriteReadAging instance(appCb);
    return &instance;
}

void WriteReadAging::checkInvalidTs(const vector<string>& tokens) const {
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

void WriteReadAging::excuteTs(const vector<string>& tokens) {
    string valueForStartLba = "";
    string valueForEndLba = "";

    for (int iter = 0; iter < TEST_MAX_ITERATE; iter++) {
        valueForStartLba = generateRandomHexString();
        valueForEndLba = generateRandomHexString();

        vector<string> writeCmd = { "write", START_LBA, valueForStartLba };
        executeCmd(writeCmd);

        writeCmd = { "write", END_LBA, valueForEndLba };
        executeCmd(writeCmd);

        vector<string> readCmd = { "read", START_LBA };
#ifdef _DEBUG
        executeCmd(readCmd);
#else
        executeCmd(readCmd, valueForStartLba);
#endif
        readCmd = { "read", END_LBA };
#ifdef _DEBUG
        executeCmd(readCmd);
#else
        executeCmd(readCmd, valueForEndLba);
#endif
    }

    return;
}