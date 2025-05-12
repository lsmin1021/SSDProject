#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "ssd_interface.h"
using std::cout;
using std::string;
using std::vector;

class TestShellApp {
public:
	TestShellApp(SsdInterface* m_ssd)
		: m_ssd(m_ssd) {
	}

	bool cmdParserAndExcute(const string& cmd);
	void writeCommand(const string& lba, const string& value);
	void readCommand(const string& lba);
	void fullWriteCommand(const string& value);
	void fullReadCommand();
	void helpCommand();

	const int m_MAX_LBA = 99;
private:
	SsdInterface* m_ssd;

	void checkLbaArg(const string& lbaString);
	void checkDataArg(const string& dataString);
	void checkReadCmNumdArg(const vector<string>& tokens);
	void checkWriteCmNumdArg(const vector<string>& tokens);
};