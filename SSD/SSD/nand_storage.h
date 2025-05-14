#pragma once
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <map>

using std::string;
using std::map;

class NandStorage {
public:
	NandStorage();

	string read(int lba);
	void write(int lba, string value);
	void erase(int lba, int cnt);

private:
	bool isEmptyLBA(int lba);

	void loadData();
	void storeData();
	string loadDataFile();
	void convertDataFile(string content);

	map<int, string> m_storage;
	const string FILE_NAME = "ssd_nand.txt";
	const string EMPTY_VALUE = "0x00000000";
};
