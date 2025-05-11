#include "test_shell_app.h"

void TestShellApp::writeCommand(const string& lba, const string& value) {
    m_ssd->writeData(lba, value);
    cout << "write " << lba << " " << value << std::endl;
}

void TestShellApp::readCommand(const string& lbaString) {
	m_ssd->readData(lbaString);
}

void TestShellApp::fullWriteCommand(const string& value) {
    for (int lba = 0; lba <= m_MAX_LBA; ++lba)
        m_ssd->writeData(std::to_string(lba), value);
}

void TestShellApp::fullReadCommand() {
    for(int lba = 0; lba <= m_MAX_LBA; ++lba)
        m_ssd->readData(std::to_string(lba));
}

void TestShellApp::helpCommand() {
    cout << "[help] command usage:\n";
    cout << "write <lba> <value>\n";
    cout << "read <lba>\n";
    cout << "fullwrite\n";
    cout << "fullread\n";
    cout << "help\n";
    cout << "exit\n";
}

bool TestShellApp::cmdParserAndExcute(const string& cmd)
{
    std::istringstream iss(cmd);
    vector<string> tokens;
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }

    const string& command = tokens[0];

    if (command == "write") {
        if (tokens.size() != 3) {
            throw std::invalid_argument("Usage: write <lba> <value>");
        }
    }
    else if (command == "read") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Usage: read <lba>");
        }
        string lbaString = tokens[1];
        std::size_t errorPos = 0;
        int lba = std::stoi(lbaString,&errorPos);
        if (errorPos != lbaString.size())
        {
            throw std::invalid_argument("Usage: decimal LBA");
        }
        if (lba > m_MAX_LBA || lba < 0) {
            throw std::invalid_argument("Usage: 0 <= LBA < 100");
        }
    }
    else if (command == "fullwrite") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Usage: fullwrite <value>");
        }
    }
    else if (command == "fullread") {
        if (tokens.size() != 1) {
            throw std::invalid_argument("Usage: fullread");
        }
    }
    else if (command == "help") {
        if (tokens.size() != 1) {
            throw std::invalid_argument("Usage: help");
        }
    }
    else if (command == "exit") {
        if (tokens.size() != 1) {
            throw std::invalid_argument("Usage: exit");
        }
    }
    else {
        throw std::invalid_argument("Invalid command: " + command);
    }


    if (command == "write") {
        string lba = tokens[1];
        string value = tokens[2];
        writeCommand(lba, value);
    }
    else if (command == "read") {
        string lba = tokens[1];
        readCommand(lba);
    }
    else if (command == "fullwrite") {
        string value = tokens[1];
        fullWriteCommand(value);
    }
    else if (command == "fullread") {
        fullReadCommand();
    }
    else if (command == "help") {
        helpCommand();
    }
    else if (command == "exit") {
        std::cout << "Exiting program." << std::endl;
        return false;
    }

    return true;
}