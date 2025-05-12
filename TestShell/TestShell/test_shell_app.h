#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>
#include <unordered_map>
#include "ssd_interface.h"
using std::cout;
using std::string;
using std::vector;
using std::ifstream;

class TestShellApp {
public:
	TestShellApp(SsdInterface* m_ssd);

	bool cmdParserAndExcute(const string& cmdcmdString);
	string autoCompleteCommand(const string& input);

	static const int MAX_LBA = 99;
	static const int TEST_SCRIPT1_LBA_STEP = 5;
	static const int TEST_SCRIPT2_REPEAT_NUM = 30;
	static const int TEST_SCRIPT2_LBA_STEP = 5;
	static const int TEST_SCRIPT3_REPEAT_NUM = 200;
	const string TEST_SCRIPT_VALUE = "0x5A5A5A5A";
	const string START_LBA = "0";
	const string END_LBA = "99";
private:
	SsdInterface* m_ssd;
	vector<string>  parseCmd(const string& cmd);
	string updateReadResult();
	string generateRandomHexString();
	string runFullWriteAndReadCompare();
	string runPartialLBAWrite();
	string runWriteReadAging();
};