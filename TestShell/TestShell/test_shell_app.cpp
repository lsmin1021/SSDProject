#include "test_shell_app.h"

// �Լ� ���� (������ �ʿ信 ���� �ۼ�)
void TestShellApp::writeCommand(int lba, const std::string& value) {
    std::cout << "[write] LBA: " << lba << ", Value: " << value << std::endl;
    // TODO: write ���� ����
}

void TestShellApp::readCommand(int lba) {
    std::cout << "[read] LBA: " << lba << std::endl;
    // TODO: read ���� ����
}

void TestShellApp::fullWriteCommand() {
    std::cout << "[fullwrite] All LBA writing..." << std::endl;
    // TODO: fullwrite ���� ����
}

void TestShellApp::fullReadCommand() {
    std::cout << "[fullread] All LBA reading..." << std::endl;
    // TODO: fullread ���� ����
}

void TestShellApp::helpCommand() {
    std::cout << "[help] ��ɾ� ����:\n";
    std::cout << "write <lba> <value>\n";
    std::cout << "read <lba>\n";
    std::cout << "fullwrite\n";
    std::cout << "fullread\n";
    std::cout << "help\n";
    std::cout << "exit\n";
}

bool TestShellApp::argParser(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "command needed.. (Please refer help)" << std::endl;
        return 1;
    }

    string command = argv[1];
    //TOdO : �Ķ������Format�� ��Ȯ�ؾ� ��, check ��ƾ �߰� �ʿ�

    if (command == "write") {
        if (argc != 4) {
            cout << "Usage: write <lba> <value>" << std::endl;
            return 1;
        }
        int lba = std::stoi(argv[2]);
        std::string value = argv[3];
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
