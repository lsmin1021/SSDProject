#pragma once
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <map>

using std::string;
using std::map;

class NandHandler {
public:
	NandHandler();

	string read(int lba);
	void write(int lba, string value);
	void erase(int lba, int cnt);

private:
	bool isEmptyLBA(int lba);
	map<int, string> getSSDData(string ssdDataStr);
	string readNand();
	void storeDataToSSD();

	map<int, string> m_ssdData;
	const string FILE_NAME = "ssd_nand.txt";
	const string EMPTY_VALUE = "0x00000000";
};
