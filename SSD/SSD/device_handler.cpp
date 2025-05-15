#include "device_handler.h"

DeviceHandler& DeviceHandler::getInstance() {
	static DeviceHandler instance;

	return instance;
}

string DeviceHandler::read(int lba) {
	string ret = m_commandBuffer.readData(lba);

	if (true == ret.empty()) {
		ret = m_nandStorage.read(lba);
	}

	return ret;
}

void DeviceHandler::write(int lba, string value) {
	if (true == m_commandBuffer.isFull()) {
		flush();
	}

	m_commandBuffer.insertCmd(Instruction().setCmdWrite().setLba(lba).setValue(value));
}

void DeviceHandler::erase(int lba, int size) {
	if (0 == size) return;
	if (true == m_commandBuffer.isFull()) {
		flush();
	}

	m_commandBuffer.insertCmd(Instruction().setCmdErase().setLba(lba).setSize(size));
}

void DeviceHandler::flush() {
	vector<Instruction> cmdList = m_commandBuffer.getBufferCommands();
	m_commandBuffer.clear();

	for (Instruction cmd : cmdList) {
		if (true == cmd.isWriteCommand()) {
			m_nandStorage.write(cmd.getLba(), cmd.getValue());
		}
		else if (true == cmd.isEraseCommand()) {
			m_nandStorage.erase(cmd.getLba(), cmd.getSize());
		}
	}

	m_nandStorage.commit();
}

