#pragma once

#include <string>
using std::string;

class SsdInterface {
public:
	virtual ~SsdInterface() = default;
	virtual void readData(const string& lba) = 0;
	virtual void writeData(const string& lba, const string& data) = 0;
	virtual void eraseData(const string& lba, const string& size) = 0;
	virtual void flush(void) = 0;
	virtual string getReadResult() = 0;
};
