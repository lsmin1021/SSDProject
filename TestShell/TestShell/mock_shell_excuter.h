#pragma once

#include "shell_excuter.h"

class MockShellExecutor : public IShellExecutor {
public:
    string lastCommand;

    int run(const string& cmd) override {
        lastCommand = cmd;
        return 0; // ��¥ ���� ����
    }
};