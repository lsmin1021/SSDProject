#include "test_shell_app.h"

void TestShellApp::writeCommand(const string& lba, const string& value) {
    m_ssd->writeData(lba, value);
    cout << "write " << lba << " " << value << std::endl;
}

void TestShellApp::readCommand(const string& lbaString) {
    int lba = std::stoi(lbaString);
    if(lba >= m_MAX_LBA){
		cout << "INVALID COMMEND" << std::endl;
		return;
	}
	m_ssd->readData(lbaString);
}

void TestShellApp::fullWriteCommand(const string& value) {
    for (int lba = 0; lba < m_MAX_LBA; ++lba)
        m_ssd->writeData(std::to_string(lba), value);
}

void TestShellApp::fullReadCommand() {
    for(int lba = 0; lba < m_MAX_LBA; ++lba)
        m_ssd->readData(std::to_string(lba));
}

void TestShellApp::helpCommand() {
    cout << "[Team Name] Clean Code\n\n";
    cout << ".######..##.......########....###....##....##.....######...#######..########..######## \n";
    cout << ".##....##.##.......##.........##.##...###...##....##....##.##.....##.##.....##.##......\n";
    cout << ".##.......##.......##........##...##..####..##....##.......##.....##.##.....##.##......\n";
    cout << ".##.......##.......######...##.....##.##.##.##....##.......##.....##.##.....##.######..\n";
    cout << ".##.......##.......##.......#########.##..####....##.......##.....##.##.....##.##......\n";
    cout << ".##....##.##.......##.......##.....##.##...###....##....##.##.....##.##.....##.##......\n";
    cout << "..######..########.########.##.....##.##....##.....######...#######..########..########\n\n";

    cout << "[Team Member] : lsmin1021 leedoyoung1234 akachoochoo CHANGHEE-H \n\n";

    cout << "[command usage]\n";
    cout << "  write <LBA> <DATA>       Write 4-byte DATA to logical block address (LBA)\n";
    cout << "  read <LBA>               Read data from the specified LBA\n";
    cout << "  fullwrite                Write default data to all LBA addresses (0 ~ 99)\n";
    cout << "  fullread                 Read all data from LBA addresses (0 ~ 99)\n";
    cout << "  exit                     Exit the shell\n";
    cout << "  help                     Show this help message\n\n";
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
        if (tokens.size() != 2) {
            throw std::invalid_argument("Usage: fullwrite <value>");
        }
        string value = tokens[1];
        fullWriteCommand(value);
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