#pragma once
#include <vector>
#include "instruction.h"

using std::vector;

class FileHandler {
public:
	static void clearDir(const string& dir);
	static void makeFile(string path);
	static vector<string> getFileList(string dir);
};

class CommandBuffer {
public:
	CommandBuffer();

	string readData(int lba);
	void insertCmd(Instruction cmd);
	vector<Instruction> getBufferCommands();
	bool isFull();
	void clear();

private:
	void loadBuffer();

	// Develope command buffer algorithm
	string getValueOnBuffer(int lba);
	void ignoreCommand(Instruction& cmd);

	bool isDirectoryExist();
	void setBufferDir();
	void loadBufferCmd(string cmd);
	void storeDataToBuffer();

	vector<Instruction> m_buffer;

	const string EMPTY_VALUE = "0x00000000";
	const string DIR_NAME = "buffer";
	const string DIR_SEARCH_PATTERN = "buffer\\*";
	
	const string EMPTY_CMD = "empty";

	const int MAX_BUFFER_SIZE = 5;
};