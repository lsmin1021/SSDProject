#pragma once
#include <string>
using std::string;

class OutputHandlerInterface;

class MsgHandler {
public:
    static MsgHandler& getInstance();
    void setMsgHandler(OutputHandlerInterface* outputHandler);
    void print(const string& msg);

#define MSG_PRINT(msg)  MsgHandler::getInstance().print(msg)

private:
    MsgHandler();
    MsgHandler(const MsgHandler&) = delete;
    MsgHandler& operator=(const MsgHandler&) = delete;

    OutputHandlerInterface* m_outputHandler = nullptr;
};