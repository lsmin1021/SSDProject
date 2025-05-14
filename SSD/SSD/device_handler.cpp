#include "device_handler.h"

DeviceHandler& DeviceHandler::getInstance() {
	static DeviceHandler instance;

	return instance;
}

string DeviceHandler::readBuffer(int lba) {
	string ret = m_commandBuffer.readDataOnBuffer(lba);

	if (true == ret.empty()) {
		ret = m_nandHandler.read(lba);
	}

	return ret;
}

bool DeviceHandler::isFull() {
	if (BUFFER_SIZE_MAX == m_commandBuffer.getUsableBufferSize()) {
		return true;
	}

	return false;
}

void DeviceHandler::flush() {
	vector<Buffer> cmdList = m_commandBuffer.getBufferCommands();
	m_commandBuffer.clear();

	for (Buffer cmd : cmdList) {
		if ("W" == cmd.getCmd()) {
			m_nandHandler.write(cmd.getLba(), cmd.getValue());
		}
		else if ("E" == cmd.getCmd()) {
			m_nandHandler.erase(cmd.getLba(), cmd.getSize());
		}
	}
}

void DeviceHandler::writeBuffer(int lba, string value) {
	m_commandBuffer.insertCmdWrite(lba, value);
}

void DeviceHandler::eraseBuffer(int lba, int size) {
	m_commandBuffer.insertCmdErase(lba, size);
}

