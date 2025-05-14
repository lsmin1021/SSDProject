#pragma once

#include <iostream>
#include <string>

using std::string;

class Instruction {
public:
	Instruction() {};

	Instruction& setCmd(string cmd);
	Instruction& setCmdWrite();
	Instruction& setCmdErase();
	Instruction& setValue(string value);
	Instruction& setLba(int lba);
	Instruction& setSize(int size);

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