#pragma once

#include "shell_excuter.h"

class MockShellExecutor : public IShellExecutor {
public:
    string lastCommand;

    int run(const string& cmd) override {
        lastCommand = cmd;
        return 0; // 가짜 성공 리턴
    }
};