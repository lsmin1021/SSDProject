#pragma once
#include <cstdlib>  
#include <string>
using std::string;

class ShellExecutorInterface {
public:
    virtual int run(const string& cmd) = 0;
    virtual ~ShellExecutorInterface() = default;
};

class RealShellExecutor : public ShellExecutorInterface {
public:
    int run(const string& cmd) override {
        return system(cmd.c_str());
    }
};