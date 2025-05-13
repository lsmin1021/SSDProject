#include "buffer_handler.h"
#include "nand_handler.h"

CommandBufferHandler& CommandBufferHandler::getInstance() {
	static CommandBufferHandler instance;

	return instance;
}

string CommandBufferHandler::readBuffer(int lba) {
	return m_commandBuffer.readDataOnBuffer(lba);
}

bool CommandBufferHandler::isFull() {
	if (BUFFER_SIZE_MAX == m_commandBuffer.getUsableBufferSize()) {
		return true;
	}

	return false;
}

void CommandBufferHandler::flush() {
	vector<Buffer> cmdList = m_commandBuffer.getBufferCommands();
	m_commandBuffer.clear();

	for (Buffer cmd : cmdList) {
		if ("W" == cmd.getCmd()) {
			NandHandler::getInstance().write(cmd.getLba(), cmd.getValue());
		}
		else if ("E" == cmd.getCmd()) {
			NandHandler::getInstance().erase(cmd.getLba(), cmd.getSize());
		}
	}
}

void CommandBufferHandler::writeBuffer(int lba, string value) {
	m_commandBuffer.insertCmd(lba, value);
}

void CommandBufferHandler::eraseBuffer(int lba, int size) {
	m_commandBuffer.insertCmd(lba, size);
}

