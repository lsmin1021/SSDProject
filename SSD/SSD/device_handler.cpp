#include "device_handler.h"

DeviceHandler& DeviceHandler::getInstance() {
	static DeviceHandler instance;

	return instance;
}

string DeviceHandler::read(int lba) {
	string ret = m_commandBuffer.readDataOnBuffer(lba);

	if (true == ret.empty()) {
		ret = m_nandHandler.read(lba);
	}

	return ret;
}

void DeviceHandler::write(int lba, string value) {
	if (true == m_commandBuffer.isFull()) {
		flush();
	}

	m_commandBuffer.insertCmdWrite(lba, value);
}

void DeviceHandler::erase(int lba, int size) {
	if (true == m_commandBuffer.isFull()) {
		flush();
	}

	m_commandBuffer.insertCmdErase(lba, size);
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

	m_nandHandler.commit();
}

