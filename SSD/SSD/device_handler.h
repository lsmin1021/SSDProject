#pragma once
#include "command_buffer.h"
#include "nand_handler.h"

class DeviceHandler {
public:
	static DeviceHandler& getInstance();

	string readBuffer(int lba);
	bool isFull();
	void flush();
	void writeBuffer(int lba, string value);
	void eraseBuffer(int lba, int size);

private:
	DeviceHandler() {};

	CommandBuffer m_commandBuffer;
	NandHandler m_nandHandler;

	const int BUFFER_SIZE_MAX = 5;
};