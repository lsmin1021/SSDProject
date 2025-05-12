#include "cmd_interface.h"

void CmdInterface::checkNumToken(const vector<string>& tokens) {
    if (tokens.size() != m_numToken) {
        throw std::invalid_argument("Invalid number of tokens");
    }
}

void CmdInterface::checkLbaArg(const string& lbaString)
{
    std::size_t errorPos = 0;
    int lba = std::stoi(lbaString, &errorPos);
    if (errorPos != lbaString.size())
    {
        throw std::invalid_argument("Usage: decimal LBA");
    }
    if (lba > MAX_LBA || lba < 0) {
        throw std::invalid_argument("Usage: 0 <= LBA < 100");
    }
}
void CmdInterface::checkDataArg(const string& dataString)
{
    if (dataString.size() != 10)
    {
        throw std::invalid_argument("Usage: 10 length data");
    }

    std::size_t errorPos = 0;
    int data = std::stoi(dataString, &errorPos, 16);
    if (errorPos != dataString.size())
    {
        throw std::invalid_argument("Usage: hex data");
    }
    if (data > 0xFFFFFFFF || data < 0) {
        throw std::invalid_argument("Usage: 0 <= LBA < 100");
    }
}

string CmdInterface::updateReadResult() {
    std::ifstream file("ssd_output.txt");

    if (!file.is_open()) {
        return "";
    }

    string result;
    getline(file, result);
    file.close();

    return result;
}