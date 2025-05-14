#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "dll_main.h"
using std::string;
using std::vector;

extern AppCb cb;

class TsInterface {
public:
	TsInterface(const string& name, int numToken);
	virtual ~TsInterface() = default;

	const string&  getName() const {
		return m_name;
	}
	const string& getShortCutName() const {
		return m_shortCutName;
	}

	virtual void checkInvalidTs(const vector<string>& tokens) const = 0;
	virtual void excuteTs(const vector<string>& tokens) = 0;

	void checkNumToken(const vector<string>& tokens) const {
		if (isValidNumToken(tokens)) return;
		throw std::invalid_argument("Invalid number of tokens");
	}
	string getReadResult() const;

	bool executeCmd(const vector<string>& cppTokens, const string& checkString = NOT_CHECK_RESULT);

private:
	bool isValidNumToken(const vector<string>& tokens) const {
		return (tokens.size() == m_numToken);
	}

	void UpdateShortCutName(){
		size_t pos = m_name.find('_');
		if (pos == std::string::npos) return;
		m_shortCutName = m_name.substr(0, pos + 1);
	}

	static vector<string> m_cbTokens;
	static string m_checkString;
	string m_name;
	string m_shortCutName;
protected:
	static const string NOT_CHECK_RESULT;
	static const int MAX_LBA = 99;
	static const int MIN_LBA = 0;
	int m_numToken;
};
