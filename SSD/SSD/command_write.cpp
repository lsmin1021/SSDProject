#include "ICommand.h"

class WriteCommand : public ICommand {
public:
	WriteCommand(NandHandler* nandHandler) : ICommand(nandHandler) { }

	bool isValid(const vector<string>& param) override {
		if (PARAMETER_COUNT != param.size()) {
			return false;
		}

		if (false == isValidLBA(param[LBA_INDEX])) {
			return false;
		}

		if (false == isValidValue(param[VALUE_INDEX])) {
			return false;
		}

		return true;
	}

	void execute(const vector<string>& param) override {
		writeDataOnAddr(std::stoi(param[LBA_INDEX]), param[VALUE_INDEX]);
	}

private:
	void writeDataOnAddr(int lba, string value) {
		m_nandHandler->write(lba, value);
	}

	const int PARAMETER_COUNT = 3;
};