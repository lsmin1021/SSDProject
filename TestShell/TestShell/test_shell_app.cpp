#include "test_shell_app.h"

void TestShellApp::writeCommand(const string& lba, const string& value) {
    cout << "[write] LBA: " << lba << ", Value: " << value << std::endl;
    // TODO: write
}

void TestShellApp::readCommand(const string& lbaString) {
    int lba = std::stoi(lbaString);
    if(lba > 99){
		cout << "INVALID COMMEND" << std::endl;
		return;
	}
	m_ssd->readData(lbaString);
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

bool TestShellApp::argParser(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "command needed.. (Please refer help)" << std::endl;
        return 1;
    }

    string command = argv[1];
    //TODO : need to check parameter format

    if (command == "write") {
        if (argc != 4) {
            cout << "Usage: write <lba> <value>" << std::endl;
            return 1;
        }
        string lba = argv[2];
        string value = argv[3];
        //writeCommand(lba, value);
    }
    else if (command == "read") {
        if (argc != 3) {
            cout << "Usage: read <lba>" << std::endl;
            return 1;
        }
        int lba = std::stoi(argv[2]);
        //readCommand(lba);
    }
    else if (command == "fullwrite") {
        //fullWriteCommand();
    }
    else if (command == "fullread") {
        //fullReadCommand();
    }
    else if (command == "help") {
        //helpCommand();
    }
    else if (command == "exit") {
        cout << "exit." << std::endl;
        return 0;
    }
    else {
        cout << "INVALID COMMAND" << std::endl;
        return 1;
    }

}
