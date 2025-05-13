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


typedef void (*ExecuteTs)(const char*);
class TestShellApp {
public:
	TestShellApp(SsdInterface* m_ssd);
	~TestShellApp();
	bool cmdParserAndExcute(const string& cmdcmdString);

private:
	SsdInterface* m_ssd;
	ExecuteTs m_executeTs;
	vector<string>  parseCmd(const string& cmd);
};