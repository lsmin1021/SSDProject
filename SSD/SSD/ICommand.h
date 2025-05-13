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

	const int LBA_INDEX = 1;
};