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
	virtual string read(int lba);
	virtual void write(int lba, string value);
	virtual void erase(int lba, int cnt);

private:
	map<int, string> getSSDData(string ssdDataStr);
	string readNand();
	void writeDataToSSD();

	map<int, string> m_ssdData;
	const string FILE_NAME = "ssd_nand.txt";
	const string EMPTY_VALUE = "0x00000000";
};
