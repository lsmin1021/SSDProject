#pragma once
#include <string>

using std::string;

class CommandBuffer {
public:
	CommandBuffer();

	//? ? ? getAllCommand();
	string readDataOnBuffer(int lba);
	int getUsableBufferSize();
	void insertCmd(int lba, int size);
	void insertCmd(int lba, string value);

private:
	// 최적화 기능들 구현

	string EMPTY_VALUE = "0x00000000";
};