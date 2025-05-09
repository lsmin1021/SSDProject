#pragma once

#include <string>
using std::string;

class SsdInterface {
public:
	virtual ~SsdInterface() = default;
	virtual void readData(string lba) = 0;
	virtual void writeData(string lba, string data) = 0;
};