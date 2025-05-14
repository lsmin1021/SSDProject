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
	bool cmdParserAndExecute(const string& cmdcmdString);

private:
	void runBasicMode(void);
	void runRunnerMode(const string& scriptFileName);
	void printInvalidArgsMessage(const string& programName);

	SsdInterface* m_ssd;
	ExecuteTs m_executeTs;
	vector<string>  parseCmd(const string& cmd);
};
