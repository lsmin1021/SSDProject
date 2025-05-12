#include "test_shell_app.h"

void TestShellApp::writeCommand(const string& lba, const string& value) {
    m_ssd->writeData(lba, value);
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

	checkInvalidCmd(tokens);

    const string& command = tokens[0];
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

void TestShellApp::checkInvalidCmd(const vector<string>& tokens) {
    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }

    const string& command = tokens[0];

    if (command == "write") {
        checkWriteCmdNumdArg(tokens);
        checkLbaArg(tokens[1]);
        checkDataArg(tokens[2]);
    }
    else if (command == "read") {
        checkReadCmdNumdArg(tokens);
        checkLbaArg(tokens[1]);
    }
    else if (command == "fullwrite") {
        checkFullWriteCmdNumdArg(tokens);
        checkDataArg(tokens[1]);
    }
    else if (command == "fullread") {
        checkFullReadCmdNumdArg(tokens);
    }
    else if (command == "help") {
        checkHelpCmdNumdArg(tokens);
    }
    else if (command == "exit") {
        checkExitCmdNumdArg(tokens);
    }
    else {
        throw std::invalid_argument("Invalid command: " + command);
    }
}

void TestShellApp::checkLbaArg(const string& lbaString)
{
    std::size_t errorPos = 0;
    int lba = std::stoi(lbaString, &errorPos);
    if (errorPos != lbaString.size())
    {
        throw std::invalid_argument("Usage: decimal LBA");
    }
    if (lba > m_MAX_LBA || lba < 0) {
        throw std::invalid_argument("Usage: 0 <= LBA < 100");
    }
}
void TestShellApp::checkDataArg(const string& dataString)
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

void TestShellApp::checkReadCmdNumdArg(const vector<string>& tokens)
{
    if (tokens.size() != 2) {
        throw std::invalid_argument("Usage: read <lba>");
    }
}

void TestShellApp::checkWriteCmdNumdArg(const vector<string>& tokens)
{
    if (tokens.size() != 3) {
        throw std::invalid_argument("Usage: write <lba> <data>");
    }
}

void TestShellApp::checkFullReadCmdNumdArg(const vector<string>& tokens)
{
    if (tokens.size() != 1) {
        throw std::invalid_argument("Usage: read");
    }
}

void TestShellApp::checkFullWriteCmdNumdArg(const vector<string>& tokens)
{
    if (tokens.size() != 2) {
        throw std::invalid_argument("Usage: write <data>");
    }
}

void TestShellApp::checkHelpCmdNumdArg(const vector<string>& tokens)
{
    if (tokens.size() != 1) {
        throw std::invalid_argument("Usage: read <lba>");
    }
}

void TestShellApp::checkExitCmdNumdArg(const vector<string>& tokens)
{
    if (tokens.size() != 1) {
        throw std::invalid_argument("Usage: read <lba>");
    }
}
