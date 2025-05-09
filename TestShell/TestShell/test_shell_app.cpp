#include "test_shell_app.h"

// 함수 선언 (구현은 필요에 따라 작성)
void TestShellApp::writeCommand(const string& lba, const string& value) {
    cout << "[write] LBA: " << lba << ", Value: " << value << std::endl;
    // TODO: write 로직 구현
}

void TestShellApp::readCommand(const string& lba) {
    cout << "[read] LBA: " << lba << std::endl;
    // TODO: read 로직 구현
}

void TestShellApp::fullWriteCommand() {
    cout << "[fullwrite] All LBA writing..." << std::endl;
    // TODO: fullwrite 로직 구현
}

void TestShellApp::fullReadCommand() {
    cout << "[fullread] All LBA reading..." << std::endl;
    // TODO: fullread 로직 구현
}

void TestShellApp::helpCommand() {
    cout << "[help] 명령어 사용법:\n";
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
    //TOdO : 파라미터의Format이 정확해야 함, check 루틴 추가 필요

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
