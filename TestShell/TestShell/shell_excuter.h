#pragma once
#include <cstdlib>  
#include <string>
using std::string;

class IShellExecutor {
public:
    virtual int run(const string& cmd) = 0;
    virtual ~IShellExecutor() = default;
};

class RealShellExecutor : public IShellExecutor {
public:
    int run(const string& cmd) override {
        return system(cmd.c_str());
    }
};