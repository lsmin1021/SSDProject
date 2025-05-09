#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "ssd_interface.h"
using std::string;
using std::cout;

class TestShellApp {
public:
	TestShellApp(SsdInterface* m_ssd)
		: m_ssd(m_ssd) {
	}

	bool argParser(int argc, char* argv[]);
	void writeCommand(const string& lba, const string& value);
	void readCommand(const string& lba);
	void fullWriteCommand();
	void fullReadCommand();
	void helpCommand();

	const int m_MAX_LBA = 100;
private:
	SsdInterface* m_ssd;
};