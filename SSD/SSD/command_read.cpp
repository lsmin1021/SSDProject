#include "ICommand.h"

class ReadCommand : public ICommand {
public:
	ReadCommand(NandHandler* nandHandler) : ICommand(nandHandler) { }

	bool isValid(const vector<string>& param) override {
		if (PARAMETER_COUNT != param.size()) {
			return false;
		}

		return isValidLBA(param[LBA_INDEX]);
	}

	void execute(const vector<string>& param) override {
		int lba = std::stoi(param[LBA_INDEX]);
		string ret = readDataOnAddr(lba);

		OutputHandler::getInstance().write(ret);
	}

private:
	string readDataOnAddr(int lba) {
		m_nandHandler->read();

		return m_nandHandler->getData(lba);
	}

	const int PARAMETER_COUNT = 2;

};