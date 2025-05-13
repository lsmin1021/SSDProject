#pragma once
#include "cmd_interface.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class SsdInterface;

class CmdInterface {
public:
	CmdInterface(const string& name, int numToken);
	virtual ~CmdInterface() = default;
	virtual void checkInvalidCmd(const vector<string>& tokens) const = 0;
	virtual void excuteCmd(const vector<string>& tokens) = 0;
	virtual void helpCmd() const  = 0;

	vector<string>  getName() const {
		return m_names;
	}

	void setSdd(SsdInterface* sdd) {
		m_ssd = sdd;
	}
protected :
	static const int MAX_LBA = 99;
	static const int MIN_LBA = 0;
	static const unsigned int MAX_DATA_VALUE = 0xFFFFFFFF;
	static const int MIN_DATA_VALUE = 0;
	SsdInterface* m_ssd;

	void checkNumToken(const vector<string>& tokens) const;
	void checkLbaArg(const string& lbaString) const;
	void checkDataArg(const string& dataString) const;
	string getReadResult() const;
protected :
	vector<string> m_names;
	bool isValidIntString(const string& string, int errorPos) const {
		return (errorPos == string.size());
	}
	bool isValidNumToken(const vector<string>& tokens) const {
		return (tokens.size() == m_numToken);
	}
	bool isValidLbaString(const string& lbaString, int errorPos) const {
		return isValidIntString(lbaString, errorPos);
	}
	bool isValidLbaRange(int lba) const {
		return (lba <= MAX_LBA && lba >= MIN_LBA);
	}
	bool isValidDataStringLen(const string& dataString) const {
		return (10 == dataString.size());
	}
	bool isValidDataString(const string& dataString, int errorPos) const {
		return isValidIntString(dataString, errorPos);
	}
	bool isValidDataRange(unsigned int data) const {
		return (data <= MAX_DATA_VALUE && int(data) >= MIN_DATA_VALUE);
	}
	const int m_numToken;
};

class TsInterface : public CmdInterface {
public:
	TsInterface(string name, int numToken) : CmdInterface(name, numToken){
		m_names.push_back(name.substr(0, 2));
	}
	~TsInterface() override {
	}
	virtual void helpCmd() const override {}

	void addCmd(CmdInterface* cmd) {
		m_cmds.push_back(cmd);
	}
private:
	vector<CmdInterface*> m_cmds;

};