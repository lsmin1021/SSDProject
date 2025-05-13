#include "command_handler.h"
#include "output_handler.h"
#include "command_write.h"
#include "command_read.h"
#include "command_erase.h"
#include "command_flush.h"

std::unique_ptr<ICommand> CommandFactory::makeCommand(const string& cmd) {
    if ("W" == cmd) {
        return std::make_unique<WriteCommand>(new NandHandler());
    }
    else if ("R" == cmd) {
        return std::make_unique<ReadCommand>(new NandHandler());
    }
    else if ("E" == cmd) {
        return std::make_unique<EraseCommand>(new NandHandler());
    }
    else if ("F" == cmd) {
        return std::make_unique<FlushCommand>(new NandHandler());
    }

    return nullptr;
}

std::unique_ptr<ICommand> CommandFactory::makeCommand(const string& cmd, NandHandler* handler) {
    if (nullptr == handler) {
        return makeCommand(cmd);
    }
    if ("W" == cmd) {
        return std::make_unique<WriteCommand>(handler);
    }
    else if ("R" == cmd) {
        return std::make_unique<ReadCommand>(handler);
    }
    else if ("E" == cmd) {
        return std::make_unique<EraseCommand>(handler);
    }
    else if ("F" == cmd) {
        return std::make_unique<FlushCommand>(handler);
    }

    return nullptr;
}

CommandHandler::CommandHandler() {
}

CommandHandler::CommandHandler(NandHandler* handler) {
    m_nandHandler = handler;
}

bool CommandHandler::handleCommand(const vector<string>& cmdArr) {
    if (false == isValidCommand(cmdArr)) {
        OutputHandler::getInstance().write("ERROR");
        return false;
    }

    executeCommand(cmdArr);

    return true;
}

bool CommandHandler::isValidCommand(const vector<string>& cmdArr) {
    if (cmdArr.empty()) return false;

    m_command = CommandFactory::makeCommand(cmdArr[0], m_nandHandler);
    if (nullptr == m_command) {
        return false;
    }

    if (false == m_command->isValid(cmdArr)) {
        OutputHandler::getInstance().write("ERROR");
        return false;
    }

    return true;
}

void CommandHandler::executeCommand(const vector<string>& cmdArr) {
    m_command->execute(cmdArr);
}