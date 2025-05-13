#include "command_read.cpp"
#include "command_write.cpp"

class CommandFactory {
public:
    static std::unique_ptr<ICommand> makeCommand(const string& cmd) {
        if ("W" == cmd) {
            return std::make_unique<WriteCommand>(new NandHandler());
        }
        else if ("R" == cmd) {
            return std::make_unique<ReadCommand>(new NandHandler());
        }

        return nullptr;
    }

    static std::unique_ptr<ICommand> makeCommand(const string& cmd, NandHandler* handler) {
        if (nullptr == handler) {
            return makeCommand(cmd);
        }
        if ("W" == cmd) {
            return std::make_unique<WriteCommand>(handler);
        }
        else if ("R" == cmd) {
            return std::make_unique<ReadCommand>(handler);
        }

        return nullptr;
    }
};

class CommandHandler {
public:
    CommandHandler() {
    }

    CommandHandler(NandHandler* handler) {
        m_nandHandler = handler;
    }

    bool handleCommand(const vector<string>& cmdArr) {
        if (false == isValidCommand(cmdArr)) {
            OutputHandler::getInstance().write("ERROR");
            return false;
        }

        executeCommand(cmdArr);

        return true;
    }

private:
    bool isValidCommand(const vector<string>& cmdArr) {
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

    void executeCommand(const vector<string>& cmdArr) {
        m_command->execute(cmdArr);
    }

    std::unique_ptr<ICommand> m_command;
    NandHandler* m_nandHandler = nullptr;
};
