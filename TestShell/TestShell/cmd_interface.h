#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "cmd_factory.h"
#include <stdexcept>

using std::string;
using std::vector;

class SsdInterface;

class CmdInterface {
public:
	CmdInterface(string name, int numToken) : m_name(name), m_numToken(numToken){
		CmdFactory::getInstance().registerCmd(this);
	}

	virtual ~CmdInterface() = default;
	virtual void checkInvalidCmd(const vector<string>& tokens) = 0;
	virtual void excuteCmd(const vector<string>& tokens) = 0;
	virtual void helpCmd() = 0;

	const string getName() const {
		return m_name;
	}
	const int MAX_LBA = 99;

	void setSdd(SsdInterface* sdd) {
		m_ssd = sdd;
	}
protected :
	SsdInterface* m_ssd;

	void checkNumToken(const vector<string>& tokens);
	void checkLbaArg(const string& lbaString);
	void checkDataArg(const string& dataString);
	string updateReadResult();
private:
	const string m_name;
	const int m_numToken;
};

class TsInterface : public CmdInterface {
public:
	TsInterface(string name, int numToken) : CmdInterface(name, numToken){}
	~TsInterface() override {
	}
	
	void addCmd(CmdInterface* cmd) {
		m_cmds.push_back(cmd);
	}
private:
	vector<CmdInterface*> m_cmds;

};