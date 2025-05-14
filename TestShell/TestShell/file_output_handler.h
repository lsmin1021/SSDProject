#pragma once
#include "output_handler_interface.h"
#include  "logger.h"

class FileOutputHandler : public OutputHandlerInterface {
public:
    void print(const string& msg) override {
        LOG_PRINT("FileOutputHandler", msg);
    }
};