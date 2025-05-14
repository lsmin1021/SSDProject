#include "cmd_interface.h"
#include "ssd_interface.h"
#include "cmd_factory.h"
#include "logger.h"
#include <fstream>
#include <stdexcept>

CmdInterface::CmdInterface(const string& name, int numToken) : m_name(name), m_numToken(numToken) {
    CmdFactory::getInstance().registerCmd(this);
}

void CmdInterface::checkNumToken(const vector<string>& tokens) const {
    if (isValidNumToken(tokens)) return;
    LOG_PRINT("CmdInterface", "Invalid number of tokens\n");
    throw std::invalid_argument("Invalid number of tokens");
}

void CmdInterface::checkLbaArg(const string& lbaString) const {
    std::size_t errorPos = 0;
    int lba = std::stoi(lbaString, &errorPos);
    if (isValidLbaString(lbaString, errorPos))
    {
        if (isValidLbaRange(lba)) return;
        LOG_PRINT("CmdInterface", "Usage: 0 <= LBA < 100\n");
        throw std::invalid_argument("Usage: 0 <= LBA < 100");
    }
    LOG_PRINT("CmdInterface", "Usage: decimal LBA\n");
    throw std::invalid_argument("Usage: decimal LBA");
}
void CmdInterface::checkDataArg(const string& dataString) const {
    if (isValidDataStringLen(dataString))
    {
        std::size_t errorPos = 0;
        unsigned int data = std::stoul(dataString, &errorPos, 16);
        if (isValidDataString(dataString, errorPos))
        {
            if (isValidDataRange(data)) return;
            LOG_PRINT("CmdInterface", "Usage: 0 <= data < 0xFFFFFFFF\n");
            throw std::invalid_argument("Usage: 0 <= data < 0xFFFFFFFF");
        }
        LOG_PRINT("CmdInterface", "Usage: hex data\n");
        throw std::invalid_argument("Usage: hex data");
    }
    LOG_PRINT("CmdInterface", "Usage: 10 length data\n");
    throw std::invalid_argument("Usage: 10 length data");
}

string CmdInterface::getReadResult() const {
    if (m_ssd)
        return m_ssd->getReadResult();
    else
        return "";
}
