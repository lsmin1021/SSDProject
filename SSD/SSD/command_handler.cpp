#include "cmd_executor.cpp"

class CommandHandler {
public:
    CommandHandler() {
        NandHandler* nandHandler = new NandHandler();
        m_writeCommand = std::make_unique<WriteCommand>(nandHandler);
        m_readCommand = std::make_unique<ReadCommand>(nandHandler);
    }

    CommandHandler(NandHandler* nandHandler) {
        m_writeCommand = std::make_unique<WriteCommand>(nandHandler);
        m_readCommand = std::make_unique<ReadCommand>(nandHandler);
    }

    bool isValidCommand(const vector<string>& cmdArr) {
        if (cmdArr.empty()) return false;

        if (cmdArr[0] == "W") return m_writeCommand->isValid(cmdArr);
        if (cmdArr[0] == "R") return m_readCommand->isValid(cmdArr);

        return false;
    }

    void executeCommand(const vector<string>& cmdArr) {
        if (cmdArr[0] == "W") m_writeCommand->execute(cmdArr);
        else if (cmdArr[0] == "R") m_readCommand->execute(cmdArr);
    }

    void handleCommand(const vector<string>& cmdArr) {
        if (isValidCommand(cmdArr)) {
            executeCommand(cmdArr);
        }
        else {
            OutputHandler::getInstance().write("ERROR");
        }
    }

private:
    std::unique_ptr<ICommand> m_writeCommand;
    std::unique_ptr<ICommand> m_readCommand;
};
