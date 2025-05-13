#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Buffer {
public:
	Buffer() {}	;
	Buffer(string cmd, string value, int lba, int size) :
		m_cmd(cmd), m_value(value), m_lba(lba), m_size(size) {
	}

	void setCmd(string cmd) { m_cmd = cmd; }
	void setValue(string value) { m_value = value; }
	void setLba(int lba) { m_lba = lba; }
	void setSize(int size) { m_size = size; }

	string getCmd() { return m_cmd; }
	string getValue() { return m_value; }
	int getLba() { return m_lba; }
	int getSize() { return m_size; }

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
	string readDataOnBuffer(int lba);
	int getUsableBufferSize();
	void insertCmd(int lba, int size);
	void insertCmd(int lba, string value);
	void clear();

private:
	// Develope command buffer algorithm
	bool isDirectoryExist();
	void setBufferDir();
	void loadBuffer();
	void loadBufferCmd(string cmd);
	void storeDataToBuffer();

	vector<Buffer> m_buffer;
	const string EMPTY_VALUE = "0x00000000";
	const string DIR_NAME = "buffer";
	const string DIR_SEARCH_PATTERN = "buffer\\*";
};