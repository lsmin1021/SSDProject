#include "write_read_aging_ts.h"

void WriteReadAging::checkInvalidCmd(const vector<string>& tokens) {
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

    for (int iter = 0; iter < TEST_SCRIPT3_REPEAT_NUM; iter++) {
        valueForStartLba = generateRandomHexString();
        valueForEndLba = generateRandomHexString();

        m_ssd->writeData(START_LBA, valueForStartLba);
        m_ssd->writeData(END_LBA, valueForEndLba);

        m_ssd->readData(START_LBA);
#ifndef _DEBUG
        if (updateReadResult().compare(valueForStartLba) != 0)
        {
            std::cout << "FAIL\n";
            return;
        }
#endif

        m_ssd->readData(END_LBA);
#ifndef _DEBUG
        if (updateReadResult().compare(valueForEndLba) != 0)
        {
            std::cout << "  FAIL\n";
            return;
        }
#endif
    }

    std::cout << "PASS\n";
}
void WriteReadAging::helpCmd() {}