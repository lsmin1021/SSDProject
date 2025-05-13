#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class ICommand {
public:
	ICommand() = default;
	virtual bool isValid(const vector<string>& param) = 0;
	virtual void execute(const vector<string>& param) = 0;

protected:
	bool toInt(const string& str, int& result) {
		try {
			size_t pos = 0;
			result = std::stoi(str, &pos);
			if (pos != str.length()) return false;
		}
		catch (std::invalid_argument&) {
			return false;
		}
		catch (std::out_of_range&) {
			return false;
		}
		return true;
	}

	bool isValidLBA(const string& lbaStr) {
		int lba;
		if (toInt(lbaStr, lba)) return (lba >= MIN_LBA && lba <= MAX_LBA);
		return false;
	}

	NandHandler* m_nandHandler;

	const int MAX_LBA = 99;
	const int MIN_LBA = 0;

	const int LBA_INDEX = 1;
};