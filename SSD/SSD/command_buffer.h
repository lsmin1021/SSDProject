#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Buffer {
public:
	Buffer() {}	;
	Buffer(string cmd, int lba, int size) :
		m_cmd(cmd), m_value(""), m_lba(lba), m_size(size) {
	}
	Buffer(string cmd, int lba, string value) :
		m_cmd(cmd), m_value(value), m_lba(lba), m_size(-1) {
	}

	void setCmd(string cmd) { m_cmd = cmd; }
	void setValue(string value) { m_value = value; }
	void setLba(int lba) { m_lba = lba; }
	void setSize(int size) { m_size = size; }

	string getCmd() { return m_cmd; }
	string getValue() { return m_value; }
	int getLba() { return m_lba; }
	int getSize() { return m_size; }

	void show() {
		std::cout << m_cmd << ", " << m_value << ", " << m_lba << ", " << m_size << std::endl;
	}

private:
	string m_cmd;
	string m_value;
	int m_lba = -1;
	int m_size = -1;
};

class CommandBuffer {
public:
	CommandBuffer();

	vector<Buffer> getBufferCommands();
	string readData(int lba);
	void insertCmd(Buffer cmd);
	bool isFull();
	void clear();

private:
	// Develope command buffer algorithm
	string getValueOnBuffer(int lba);
	void ignoreCommand(Buffer& cmd);

	bool isDirectoryExist();
	void setBufferDir();
	void loadBuffer();
	void loadBufferCmd(string cmd);
	void storeDataToBuffer();
	Buffer parseBufferCmd(string bufferCmd);
	string makeBufferCmd(int index, Buffer& bufferCmd);

	vector<Buffer> m_buffer;
	const string EMPTY_VALUE = "0x00000000";
	const string DIR_NAME = "buffer";
	const string DIR_SEARCH_PATTERN = "buffer\\*";
	
	const string EMPTY_CMD = "empty";
	const string WRITE_CMD = "W";
	const string ERASE_CMD = "E";

	const int MAX_BUFFER_SIZE = 5;
};