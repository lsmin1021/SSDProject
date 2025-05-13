#include "Logger.h"

Logger::Logger() {
    logFile.open(logFileName, std::ios::app);
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.flush();
        logFile.close();
        rotateIfNeeded();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setMode(LogMode mode) {
    logMode = mode;
}

std::string Logger::getCurrentTimeString() {
    std::time_t t = std::time(nullptr);
    std::tm tm_buf; 
    localtime_s(&tm_buf, &t);

    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y.%m.%d %H:%M", &tm_buf);
    return buffer;
}

void Logger::rotateIfNeeded() {
    struct stat stat_buf;
    if (stat(logFileName.c_str(), &stat_buf) == 0 && stat_buf.st_size > maxFileSize) {
        logFile.close();

        std::string timestamp = getCurrentTimeString();
        for (char& c : timestamp) {
            if (c == ':' || c == ' ') c = '_';
        }

        std::string newFileName = "until_" + timestamp + ".log";
        std::rename(logFileName.c_str(), newFileName.c_str());

        logFile.open(logFileName, std::ios::trunc);
    }
}

void Logger::log(const std::string& className, const std::string& functionName, const std::string& message) {
    rotateIfNeeded();

    std::ostringstream oss;
    string funcDisplay = functionName + "() ";
    oss << "[" << getCurrentTimeString() << "] "
        << className << "."
        << std::left << std::setw(30) << funcDisplay
        << ": " << message;

    std::string output = oss.str();

    if (logMode == LogMode::ConsoleAndFile) {
        std::cout << message;
    }

    if (logFile.is_open()) {
        logFile << output;
    }
}
