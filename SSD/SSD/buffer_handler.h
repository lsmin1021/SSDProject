#pragma once
#include "command_buffer.h"


class CommandBufferHandler {
public:
	static CommandBufferHandler& getInstance();

	string readBuffer(int lba);
	bool isFull();
	void flush();
	void writeBuffer(int lba, string value);
	void eraseBuffer(int lba, int size);

private:
	CommandBufferHandler() {};

	CommandBuffer m_commandBuffer;

	const int BUFFER_SIZE_MAX = 5;
};