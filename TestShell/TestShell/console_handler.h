#pragma once
#include "output_handler_interface.h"
#include <iostream>

class ConsoleOutputHandler : public OutputHandlerInterface {
public:
    void print(const string& msg) override {
        std::cout << msg;
    }
};