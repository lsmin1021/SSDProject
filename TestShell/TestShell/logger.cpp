#include "Logger.h"

Logger::Logger() {
    logFile.open(logFileName, std::ios::app);
}

Logger::~Logger() {
    flushLog();
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setMode(LogMode mode) {
    logMode = mode;
}

void Logger::flushLog()
{
    if (logFile.is_open()) {
        logFile.flush();
        logFile.close();
    }
}

string Logger::getCurrentTimeString() {
    std::time_t t = std::time(nullptr);
    std::tm tm_buf; 
    localtime_s(&tm_buf, &t);

    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y.%m.%d %H:%M:%S", &tm_buf);
    return buffer;
}

void compressOldLogsWin(const string& directory, const string& excludeFile) {
    string searchPattern = directory + "\\until_*.log";

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "No matching log files found.\n";
        return;
    }

    do {
        string fileName = findData.cFileName;
        string fullPathOld = directory + "\\" + fileName;

        if(fileName == excludeFile) break;
      
        size_t pos = fileName.rfind(".log");
        if (pos != string::npos) {
            string newFileName = fileName.substr(0, pos) + ".zip";
            string fullPathNew = directory + "\\" + newFileName;
            MoveFileA(fullPathOld.c_str(), fullPathNew.c_str());
        }

    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);
}

void Logger::rotateIfNeeded() {
    struct stat stat_buf;
    if (stat(logFileName.c_str(), &stat_buf) == 0 && stat_buf.st_size > MAX_FILE_SIZE) {
        logFile.close();

        string timestamp = getCurrentTimeString();
        for (char& c : timestamp) {
            if (c == ':' || c == ' ') c = '_';
        }

        string newFileName = "until_" + timestamp + ".log";
        std::rename(logFileName.c_str(), newFileName.c_str());

        logFile.open(logFileName, std::ios::trunc);

        compressOldLogsWin(".", newFileName);
    }
}

void Logger::log(const string& className, const string& functionName, const string& message) {
    std::ostringstream oss;
    string funcDisplay = extractFunctionName(functionName + "() ");
    oss << "[" << getCurrentTimeString() << "] "
        << className << "."
        << std::left << std::setw(30) << funcDisplay
        << ": " << message;

    string output = oss.str();

    if (logMode == LogMode::ConsoleAndFile) {
        std::cout << message;
    }

    if (logFile.is_open()) {
        logFile << output;
        rotateIfNeeded();
    }
}

string Logger::extractFunctionName(const string& fullName) {
    size_t pos = fullName.rfind("::");
    if (pos != string::npos)
        return fullName.substr(pos + 2);
    return fullName;
}