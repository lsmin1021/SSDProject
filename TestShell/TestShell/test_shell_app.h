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

private:
	SsdInterface* m_ssd;
	vector<string>  parseCmd(const string& cmd);
};