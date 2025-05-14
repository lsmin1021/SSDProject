#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "dll_main.h"
using std::string;
using std::vector;

extern AppCb cb;

class FailException : public std::exception {
};

class TsInterface {
public:
	TsInterface(const string& name, int numToken);
	virtual ~TsInterface() = default;

	vector<string>  getName() const {
		return m_names;
	}

	virtual void checkInvalidTs(const vector<string>& tokens) const = 0;
	virtual void excuteTs(const vector<string>& tokens) = 0;

	void checkNumToken(const vector<string>& tokens) const {
		if (isValidNumToken(tokens)) return;
		throw std::invalid_argument("Invalid number of tokens");
	}
	string getReadResult() const;

	bool executeCmd(const vector<string>& cppTokens) {
		m_numCbToken = converTokenCpptoC(cppTokens);
		return cb.excueteCmd(m_numCbToken, m_cbTokens);
		return true;
	}
	int converTokenCpptoC(const vector<string>& cppTokens);
private:
	static char m_cbTokens[10][100];
	static int m_numCbToken;
	bool isValidNumToken(const vector<string>& tokens) const {
		return (tokens.size() == m_numToken);
	}
	vector<string> m_names;
protected:
	static const int MAX_LBA = 99;
	static const int MIN_LBA = 0;
	const int m_numToken;
};
