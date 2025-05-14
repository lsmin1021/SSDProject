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


typedef void (*ExecuteTs)(const char*);
class SsdInterface;

class TestShellApp {
public:
	TestShellApp(SsdInterface* m_ssd);
	~TestShellApp() = default;
	void run(int argc, char* argv[]);
	bool cmdParserAndExcute(const string& cmdcmdString);

private:
	void runBasic(void);
	void runRunner(string scriptFileName);
	SsdInterface* m_ssd;
	ExecuteTs m_executeTs;
	vector<string>  parseCmd(const string& cmd);
};
