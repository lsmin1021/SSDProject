#pragma once

#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <sys/stat.h>

using std::string;

enum class LogMode {
    FileOnly,
    ConsoleAndFile
};

class Logger {
public:
    static Logger& getInstance();

    void setMode(LogMode mode);

    void log(const string& className, const string& functionName,
        const string& message); 

    #define LOG_PRINT(cls, msg)  Logger::getInstance().log(cls, __FUNCTION__, msg)

private:
    Logger();
    Logger(const Logger&) = delete;
    ~Logger();
    Logger& operator=(const Logger&) = delete;

    void rotateIfNeeded();
    string getCurrentTimeString();

private:
    const string logFileName = "latest.log";
    const size_t K_BYTE = 1024;
    const size_t MAX_FILE_SIZE = 10 * K_BYTE;
    LogMode logMode = LogMode::ConsoleAndFile;
    std::ofstream logFile;
};

