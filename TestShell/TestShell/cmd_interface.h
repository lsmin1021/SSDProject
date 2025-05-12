#pragma once
#include <string>
#include <vector>

#include "cmd_factory.h"
#include <stdexcept>

using std::string;
using std::vector;

class CmdInterface {
public:
	CmdInterface(string name, int numToken) : m_name(name), m_numToken(numToken){
		CmdFactory::getInstance().registerCmd(this);
	}

	virtual ~CmdInterface() = default;
	virtual void checkInvalidCmd(const vector<string>& tokens) = 0;
	virtual void excuteCmd(const vector<string>& args) = 0;
	virtual void helpCmd() = 0;

	const string getName() const {
		return m_name;
	}
protected :
	void checkInvalidNumToken(const vector<string>& tokens) {
		if (tokens.size() != m_numToken) {
			throw std::invalid_argument("Invalid number of tokens");
		}
	}

private:
	const string m_name;
	const int m_numToken;
};

class CompsiteCmdInterface : public CmdInterface {
public:
	CompsiteCmdInterface(string name, int numToken) : CmdInterface(name, numToken){}
	~CompsiteCmdInterface() override {
	}
	
	void addCmd(CmdInterface* cmd) {
		m_cmds.push_back(cmd);
	}
private:
	vector<CmdInterface*> m_cmds;

};