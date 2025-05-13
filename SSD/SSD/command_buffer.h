#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class CommandBuffer {
public:
	typedef struct {
		string cmd;
		string value;
		int lba = -1;
		int size = -1;
	} ST_COMMAND;

	CommandBuffer();

	//? ? ? getAllCommand();
	string readDataOnBuffer(int lba);
	int getUsableBufferSize();
	void insertCmd(int lba, int size);
	void insertCmd(int lba, string value);

private:
	// Develope command buffer algorithm

	vector<ST_COMMAND> m_buffer;
	string EMPTY_VALUE = "0x00000000";
};