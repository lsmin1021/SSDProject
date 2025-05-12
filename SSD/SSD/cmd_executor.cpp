#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "nand_handler.cpp"

using std::string;
using std::map;

class CmdChecker {
public:
	static bool isValidLBA(int lba) {
		if (0 > lba || 100 <= lba) {
			return false;
		}

		return true;
	}

	static bool isValidValue(string value) {
		if (0 != value.find("0x")) {
			return false;
		}
		else if (10 != value.length()) {
			return false;
		}
		else {
			for (int i = 2; i < value.length(); i++) {
				if (('0' <= value[i] && '9' >= value[i]) ||
					('a' <= value[i] && 'f' >= value[i]) ||
					('A' <= value[i] && 'F' >= value[i])) {
					continue;
				}

				return false;
			}
		}

		return true;
	}
};

class CmdExecutor {
public:
	CmdExecutor() {}

	string read(int lba) {
		if (false == CmdChecker::isValidLBA(lba)) {
			throw std::exception("[READ ERROR] Out of lba");
		}

		string ssdDataStr = readNand();
		map<int, string> ssdData = getSSDData(ssdDataStr);
		if (ssdData.find(lba) == ssdData.end()) {
			return EMPTY_VALUE;
		}
		else {
			return ssdData[lba] ;
		}
	}

	void write(int lba, string value) {
		if (false == CmdChecker::isValidLBA(lba)) {
			throw std::exception("[WRITE ERROR] Out of lba");
		}
		if (false == CmdChecker::isValidValue(value)) {
			throw std::exception("[WRITE ERROR] Invalid value to write.");
		}

		string ssdDataStr = readNand();
		map<int, string> ssdData = getSSDData(ssdDataStr);

		if (ssdData.find(lba) == ssdData.end()) {
			ssdData.insert(std::make_pair(lba, value));
		}
		else {
			ssdData[lba] = value;
		}

		writeNand(ssdData);
	}

private:
	map<int, string> getSSDData(string ssdDataStr) {
		map<int, string> ret;
		std::istringstream iss(ssdDataStr);
		string line;

		while (std::getline(iss, line) ) {
			int lba = std::stoi(line.substr(0, line.find(" ")));
			string value = line.substr(line.find(" ")+1);

			ret.insert(std::make_pair(lba, value));
		}

		return ret;
	}

	string readNand() {
		std::ifstream fs;
		string content;

		fs.open("ssd_nand.txt");

		string line;
		while (getline(fs, line) ) {
			content.append(line).append("\n");
		}

		fs.close();

		return content;
	}

	void writeNand(map<int, string> ssdData) {
		std::ofstream fs;

		fs.open("ssd_nand.txt", std::ofstream::out | std::ofstream::trunc);

		for (auto d : ssdData) {
			fs << std::to_string(d.first) << " " << d.second << std::endl;
		}

		fs.close();
	}

	const string EMPTY_VALUE = "0x00000000";
};
