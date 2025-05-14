#pragma once
#include "command_buffer.h"
#include "nand_storage.h"

class DeviceHandler {
public:
	static DeviceHandler& getInstance();

	string read(int lba);
	void write(int lba, string value);
	void erase(int lba, int size);
	void flush();

private:
	DeviceHandler() {};

	CommandBuffer m_commandBuffer;
	NandStorage m_nandHandler;
};