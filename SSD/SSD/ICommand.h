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

protected:
	int toInt(const string& sizeStr) {
		int size;
		try {
			size_t pos = 0;
			size = std::stoi(sizeStr, &pos);
			if (pos != sizeStr.length()) return -1;
		}
		catch (std::invalid_argument&) {
			return -1;
		}
		catch (std::out_of_range&) {
			return -1;
		}
		return size;
	}

	bool isValidLBA(const string& lbaStr) {
		int lba = toInt(lbaStr);
		return (lba >= MIN_LBA && lba <= MAX_LBA);
	}


	NandHandler* m_nandHandler;

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;

	const int LBA_INDEX = 1;
};