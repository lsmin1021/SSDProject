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

	void writeCommand(int lba, const std::string& value);
	void readCommand(int lba);
	void fullWriteCommand();
	void fullReadCommand();
	void helpCommand();
	bool argParser(int argc, char* argv[]);
private:
	SsdInterface* m_ssd;	
};