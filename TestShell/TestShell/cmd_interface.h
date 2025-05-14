#pragma once

#include <string>
#include <vector>
#include <iomanip>

using std::string;
using std::vector;

class SsdInterface;

class FailException : public std::exception {
};

class ExitException : public std::exception {
};

class CmdInterface {
public:
	CmdInterface(const string& name, int numToken);
	virtual ~CmdInterface() = default;
	virtual void checkInvalidCmd(const vector<string>& tokens) const = 0;
	virtual void excuteCmd(const vector<string>& tokens) = 0;
	virtual void helpCmd() const = 0;
	string getReadResult() const;

	string  getName() const {
		return m_name;
	}

	void setSdd(SsdInterface* sdd) {
		m_ssd = sdd;
	}
protected:
	static const int MAX_LBA = 99;
	static const int MIN_LBA = 0;
	static const unsigned int MAX_DATA_VALUE = 0xFFFFFFFF;
	static const int MIN_DATA_VALUE = 0;

	void checkNumToken(const vector<string>& tokens) const;
	void checkLbaArg(const string& lbaString) const;
	void checkDataArg(const string& dataString) const;
	string m_name;
	bool isValidIntString(const string& string, size_t errorPos) const {
		return (errorPos == string.size());
	}
	bool isValidNumToken(const vector<string>& tokens) const {
		return (tokens.size() == m_numToken);
	}
	bool isValidLbaString(const string& lbaString, size_t errorPos) const {
		return isValidIntString(lbaString, errorPos);
	}
	bool isValidLbaRange(int lba) const {
		return (lba <= MAX_LBA && lba >= MIN_LBA);
	}
	bool isValidDataStringLen(const string& dataString) const {
		return (10 == dataString.size());
	}
	bool isValidDataString(const string& dataString, size_t errorPos) const {
		return isValidIntString(dataString, errorPos);
	}
	bool isValidDataRange(unsigned int data) const {
		return (data <= MAX_DATA_VALUE && data >= MIN_DATA_VALUE);
	}
	const int m_numToken;
	SsdInterface* m_ssd = nullptr;
};

