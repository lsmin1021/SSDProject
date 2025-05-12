#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "ssd_interface.h"
using std::cout;
using std::string;
using std::vector;
using std::ifstream;

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

	void checkInvalidCmd(const vector<string>& tokens);
	void checkLbaArg(const string& lbaString);
	void checkDataArg(const string& dataString);
	void checkReadCmdNumdArg(const vector<string>& tokens);
	void checkWriteCmdNumdArg(const vector<string>& tokens);
	void checkFullReadCmdNumdArg(const vector<string>& tokens);
	void checkFullWriteCmdNumdArg(const vector<string>& tokens);
	void checkHelpCmdNumdArg(const vector<string>& tokens);
	void checkExitCmdNumdArg(const vector<string>& tokens);
	string updateReadResult();
};