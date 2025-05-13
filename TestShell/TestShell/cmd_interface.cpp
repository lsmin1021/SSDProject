#include "cmd_interface.h"
#include "cmd_factory.h"
#include <fstream>
#include <stdexcept>

CmdInterface::CmdInterface(const string& name, int numToken) : m_numToken(numToken) {
    m_names.push_back(name);
    CmdFactory::getInstance().registerCmd(this);
}

void CmdInterface::checkNumToken(const vector<string>& tokens) const {
    if (isValidNumToken(tokens)) return;
    throw std::invalid_argument("Invalid number of tokens");
}

void CmdInterface::checkLbaArg(const string& lbaString) const {
    std::size_t errorPos = 0;
    int lba = std::stoi(lbaString, &errorPos);
    if (isValidLbaString(lbaString, errorPos))
    {
        if (isValidLbaRange(lba)) return;
        throw std::invalid_argument("Usage: 0 <= LBA < 100");
    }
    throw std::invalid_argument("Usage: decimal LBA");
}
void CmdInterface::checkDataArg(const string& dataString) const {
    if (isValidDataStringLen(dataString))
    {
        std::size_t errorPos = 0;
        unsigned int data = std::stoi(dataString, &errorPos, 16);
        if (isValidDataString(dataString, errorPos))
        {
            if (isValidDataRange(data)) return;
            throw std::invalid_argument("Usage: 0 <= data < 0xFFFFFFFF");
        }
        throw std::invalid_argument("Usage: hex data");
    }
    throw std::invalid_argument("Usage: 10 length data");
}

string CmdInterface::getReadResult() const {
    std::ifstream file("ssd_output.txt");

    if (!file.is_open()) {
        return "";
    }

    string result;
    getline(file, result);
    file.close();

    return result;
}