#include "test_shell_app.h"

void TestShellApp::writeCommand(const string& lba, const string& value) {
    cout << "[write] LBA: " << lba << ", Value: " << value << std::endl;
    // TODO: write
}

void TestShellApp::readCommand(const string& lba) {
    cout << "[read] LBA: " << lba << std::endl;
    // TODO: read
}

void TestShellApp::fullWriteCommand() {
    cout << "[fullwrite] All LBA writing..." << std::endl;
    // TODO: fullwrite
}

void TestShellApp::fullReadCommand() {
    cout << "[fullread] All LBA reading..." << std::endl;
    // TODO: fullread
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
    vector<std::string> tokens;
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
        string lba = tokens[1];
        string value = tokens[2];
        writeCommand(lba, value);
    }
    else if (command == "read") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Usage: read <lba>");
        }
        string lba = tokens[1];
        readCommand(lba);
    }
    else if (command == "fullwrite") {
        if (tokens.size() != 1) {
            throw std::invalid_argument("Usage: fullwrite");
        }
        fullWriteCommand();
    }
    else if (command == "fullread") {
        if (tokens.size() != 1) {
            throw std::invalid_argument("Usage: fullread");
        }
        fullReadCommand();
    }
    else if (command == "help") {
        if (tokens.size() != 1) {
            throw std::invalid_argument("Usage: help");
        }
        helpCommand();
    }
    else if (command == "exit") {
        if (tokens.size() != 1) {
            throw std::invalid_argument("Usage: exit");
        }
        std::cout << "Exiting program." << std::endl;
        return false;
    }
    else {
        throw std::invalid_argument("Invalid command: " + command);
    }

    return true;
}
