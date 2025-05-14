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

enum ShellMode {
	MODE_BASIC = 0,
	MODE_RUNNER = 1,
	MODE_NULL = 2
};

class TestShellApp {
public:
	TestShellApp(SsdInterface* m_ssd);
	~TestShellApp() = default;
	void run(int argc, char* argv[]);
	bool cmdParserAndExecute(const string& cmdcmdString);
private:
	void runBasicMode(void);
	void runRunnerMode(const string& scriptFileName);
	bool executeSsdComand(vector<string> cmdTokens);
	void executeTestScript(const vector<string>& cmdTokens);

	void printInvalidArgsMessage(const string& programName);

	void setShellMode(ShellMode mode) {
		m_shellMode = mode;
	}
	ShellMode getShellMode() {
		return m_shellMode;
	}

	SsdInterface* m_ssd;
	vector<string>  parseCmd(const string& cmd);

	ShellMode m_shellMode;
};
