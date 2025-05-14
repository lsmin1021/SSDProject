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

using std::cout;
using std::string;
using std::vector;
using std::ifstream;

class SsdInterface;

class TestShellApp {
public:
	TestShellApp(SsdInterface* ssd);
	bool cmdParserAndExcute(const string& cmdcmdString);

private:
	SsdInterface* m_ssd;
	vector<string>  parseCmd(const string& cmd);
};
