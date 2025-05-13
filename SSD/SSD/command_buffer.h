#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Buffer {
public:
	Buffer(string cmd, string value, int lba, int size) :
		cmd(cmd), value(value), lba(lba), size(size) {
	}

	string getCmd() { return cmd; }
	string getValue() { return value; }
	int getLba() { return lba; }
	int getSize() { return size; }

private:
	string cmd;
	string value;
	int lba = -1;
	int size = -1;
};

class CommandBuffer {
public:

	CommandBuffer();

	//? ? ? getAllCommand();
	string readDataOnBuffer(int lba);
	int getUsableBufferSize();
	void insertCmd(int lba, int size);
	void insertCmd(int lba, string value);
	void clear();

private:
	// Develope command buffer algorithm

	vector<Buffer> m_buffer;
	string EMPTY_VALUE = "0x00000000";
};