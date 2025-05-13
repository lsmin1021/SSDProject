#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "nand_handler.h"

using std::string;
using std::vector;

class ICommand {
public:
	ICommand(NandHandler* nandHandler) : m_nandHandler(nandHandler) {}

	virtual bool isValid(const vector<string>& param) = 0;
	virtual void execute(const vector<string>& param) = 0;

	bool isValidLBA(const string& lbaStr) {
		try {
			size_t pos = 0;
			int lba = std::stoi(lbaStr, &pos);
			if (pos != lbaStr.length())	return false;
			if (lba < MIN_LBA || lba > MAX_LBA) return false;
		}
		catch (std::invalid_argument&) {
			return false;
		}
		catch (std::out_of_range&) {
			return false;
		}
		return true;
	}


	NandHandler* m_nandHandler;

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;
	const int DATA_VALUE_LENGTH = 10;

	const int LBA_INDEX = 1;
};

class ReadCommand : public ICommand {
public:
	ReadCommand(NandHandler* nandHandler);
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	string readDataOnAddr(int lba);

	const int PARAMETER_COUNT = 2;
};

class WriteCommand : public ICommand {
public:
	WriteCommand(NandHandler* nandHandler);
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	void writeDataOnAddr(int lba, string value);
	bool isValidValue(const string& valueStr);

	const int PARAMETER_COUNT = 3;
	const int VALUE_INDEX = 2;
};

class EraseCommand : public ICommand {
public:
	EraseCommand(NandHandler* nandHandler);
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	void eraseData(int lba, int size);
	bool isValidSize(const string& valueStr);

	const int PARAMETER_COUNT = 3;
	const int SIZE_INDEX = 2;

	const int MAX_SIZE = 10;
	const int MIN_SIZE = 0;
};

class FlushCommand : public ICommand {
public:
	FlushCommand(NandHandler* nandHandler);
	bool isValid(const vector<string>& param) override;
	void execute(const vector<string>& param) override;

private:
	void flushBuffer();

	const int PARAMETER_COUNT = 1;
};