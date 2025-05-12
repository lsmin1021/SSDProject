#include "test_shell_app.h"
#include "cmd_factory.h"
#include "cmd_interface.h"

TestShellApp::TestShellApp(SsdInterface* m_ssd): m_ssd(m_ssd) {
    CmdFactory::getInstance().setSdd(m_ssd);
}

void TestShellApp::writeCommand(const string& lba, const string& value) {
    m_ssd->writeData(lba, value);
#ifndef _DEBUG
    cout << "[Write] Done\n";
#endif
}

void TestShellApp::readCommand(const string& lbaString) {
	m_ssd->readData(lbaString);
#ifndef _DEBUG
    cout << "[Read] LBA " << lbaString << " : " << updateReadResult() << std::endl;
#endif
}

void TestShellApp::fullWriteCommand(const string& value) {
    for (int lba = 0; lba <= MAX_LBA; ++lba) {
        cout << lba << " " << value << std::endl;
        m_ssd->writeData(std::to_string(lba), value);
        
    }
        
}

void TestShellApp::fullReadCommand() {
    for (int lba = 0; lba <= MAX_LBA; ++lba)
    {
        m_ssd->readData(std::to_string(lba));
#ifndef _DEBUG
        cout << "[Read] LBA " << lba << " : " << updateReadResult();
#endif
    }
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

bool TestShellApp::cmdParserAndExcute(const string& cmdString)
{
    vector<string> tokens = parseCmd(autoCompleteCommand(cmdString));
    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }
    CmdInterface* cmdObj = CmdFactory::getInstance().getCmd(tokens[0]);

    cmdObj->checkInvalidCmd(tokens);

    //cmdObj->excuteCmd(tokens);

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
    else if (command == "1_FullWriteAndReadCompare" || command == "1_") {
        
    }
    else if (command == "2_PartialLBAWrite" || command == "2_") {
        
    }
    else if (command == "3_WriteReadAging" || command == "3_") {
        
    }
    return true;
}



vector<string>  TestShellApp::parseCmd(const string& cmd) {
    std::istringstream iss(cmd);
    vector<string> tokens;
    string token;
    
    cout << cmd << std::endl;

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


string TestShellApp::updateReadResult() {
    ifstream file("ssd_output.txt");

    if (!file.is_open()) {
        return "";
    }

    string result;
    getline(file, result);
    file.close();

    return result;
}

string TestShellApp::generateRandomHexString() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

    uint32_t randomValue = dist(gen);

    std::stringstream ss;
    ss << "0x" << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << randomValue;
    return ss.str(); // ¿¹: "0x1A2B3C4D"
}

string TestShellApp::runFullWriteAndReadCompare()
{ 
    int lba = 0;

    while (lba <= MAX_LBA) {
        for (int addr = lba; addr < lba + TEST_SCRIPT1_LBA_STEP; addr++) {
            m_ssd->writeData(std::to_string(addr), TEST_SCRIPT_VALUE);
        }

        for (int addr = lba; addr < lba + TEST_SCRIPT1_LBA_STEP; addr++) {
            m_ssd->readData(std::to_string(addr));
#ifndef _DEBUG
            if (updateReadResult() != TEST_SCRIPT_VALUE)
            {
                cout << "FAIL\n";
                return "FAIL";
            }
#endif
        }
        lba += TEST_SCRIPT1_LBA_STEP;
        
    }

    cout << "PASS\n";
    return "PASS";
}

string TestShellApp::runPartialLBAWrite()
{
    int iter = 0;
    vector<string> test_addr = { "4", "0", "3", "1", "2" };

    while (iter < TEST_SCRIPT2_REPEAT_NUM) {        
        for(auto addr : test_addr)
            m_ssd->writeData(addr, TEST_SCRIPT_VALUE);
       

        for (int addr = 0; addr < TEST_SCRIPT2_LBA_STEP; addr++) {
            m_ssd->readData(std::to_string(addr));
#ifndef _DEBUG
            if (updateReadResult().compare(TEST_SCRIPT_VALUE) != 0)
            {
                cout << "FAIL\n";
                return "FAIL";
            }
#endif
        }
        iter++;
    }

    cout << "PASS\n";
    return "PASS";
}

string TestShellApp::runWriteReadAging()
{
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
            cout << "FAIL\n";
            return "FAIL";
        }
#endif

        m_ssd->readData(END_LBA);
#ifndef _DEBUG
        if (updateReadResult().compare(valueForEndLba) != 0)
        {
            cout << "  FAIL\n";
            return "FAIL";
        }
#endif
    }

    cout << "PASS\n";
    return "PASS";
}