#include <iostream>
#include "command_handler.h"
#include "output_handler.h"
#include "command_write.h"
#include "command_read.h"
#include "command_erase.h"
#include "command_flush.h"

std::unique_ptr<ICommand> CommandFactory::makeCommand(const string& cmd) {
    if ("W" == cmd) {
        return std::make_unique<WriteCommand>();
    }
    else if ("R" == cmd) {
        return std::make_unique<ReadCommand>();
    }
    else if ("E" == cmd) {
        return std::make_unique<EraseCommand>();
    }
    else if ("F" == cmd) {
        return std::make_unique<FlushCommand>();
    }

    return nullptr;
}

CommandHandler::CommandHandler() {
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

    m_command = CommandFactory::makeCommand(cmdArr[0]);
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