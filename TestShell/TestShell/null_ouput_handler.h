#pragma once
#include "output_handler_interface.h"
class NullOutputHandler : public OutputHandlerInterface {
public:
    void print(const string& msg) override {
        // Do Noting for test speed
    }
};