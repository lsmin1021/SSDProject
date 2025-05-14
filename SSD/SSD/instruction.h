#pragma once

#include <iostream>
#include <string>

using std::string;

class Instruction {
public:
	Instruction() {};
	Instruction(string cmd, int lba, int size) :
		m_cmd(cmd), m_value(""), m_lba(lba), m_size(size) {
	}
	Instruction(string cmd, int lba, string value) :
		m_cmd(cmd), m_value(value), m_lba(lba), m_size(-1) {
	}

	void setCmd(string cmd);
	void setValue(string value);
	void setLba(int lba);
	void setSize(int size);

	string getCmd();
	string getValue();
	int getLba();
	int getSize();

	bool isWriteCommand();
	bool isEraseCommand();

	void show();

private:
	string m_cmd;
	string m_value;
	int m_lba = -1;
	int m_size = -1;

	string WRITE_CMD = "W";
	string ERASE_CMD = "E";
};