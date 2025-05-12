
#include <iostream>
#include <vector>

#include "output_handler.cpp"
#include "nand_handler.cpp"

using std::vector;

class ICommand {
public:
	ICommand() {
		m_nandHandler = new NandHandler();
	}

	virtual bool isValid(const vector<string>& param) = 0;
	virtual void execute(const vector<string>& param) = 0;

	bool isValidLBA(const string& lbaStr) {
		size_t pos = 0;
		int lba = std::stoi(lbaStr, &pos);

		if (pos != lbaStr.length())
			return false;
		else if (lba < MIN_LBA || lba > MAX_LBA)
			return false;

		return true;
	}

	bool isValidValue(const string& valueStr) {
		if (valueStr.length() != DATA_VALUE_LENGTH)
			return false;
		if (valueStr.find("0x") != 0)
			return false;

		for (char ch : valueStr.substr(2)) {
			if (!isxdigit(static_cast<unsigned char>(ch)))
				return false;
		}

		return true;
	}

	NandInterface* m_nandHandler;

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;
	const int DATA_VALUE_LENGTH = 10;

	const int LBA_INDEX = 1;
	const int VALUE_INDEX = 2;
};

class ReadCommand : public ICommand {
public:
	bool isValid(const vector<string>& param) override {
		if (2 > param.size()) {
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
};

class WriteCommand : public ICommand {
public:
	bool isValid(const vector<string>& param) override {
		if (3 > param.size()) {
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
		m_nandHandler->read();

		m_nandHandler->write(lba, value);
	}
};