#pragma once
#include <string>
using std::string;

class OutputHandlerInterface {
public:
    virtual ~OutputHandlerInterface() = default;
    virtual void print(const string& msg) = 0;
};