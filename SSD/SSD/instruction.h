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

	Instruction& setInstString(const string& instStr);
	string getInstString();

	bool isWriteCommand();
	bool isEraseCommand();

	static bool isMergeable(Instruction& inst1, Instruction& inst2);
	static Instruction mergeInst(Instruction& inst1, Instruction& inst2);

	void show();

private:
	string m_cmd;
	string m_value;
	int m_lba = -1;
	int m_size = -1;

	string WRITE_CMD = "W";
	string ERASE_CMD = "E";
	string DELIMITER = "_";
};