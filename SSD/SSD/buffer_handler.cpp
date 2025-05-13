#include "buffer_handler.h"
#include "nand_handler.h"

CommandBufferHandler& CommandBufferHandler::getInstance() {
	static CommandBufferHandler instance;

	return instance;
}

string CommandBufferHandler::readBuffer(int lba) {
	string ret = m_commandBuffer.readDataOnBuffer(lba);

	if (true == ret.empty()) {
		ret = NandHandler::getInstance().read(lba);
	}

	return ret;
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
	m_commandBuffer.insertCmdWrite(lba, value);
}

void CommandBufferHandler::eraseBuffer(int lba, int size) {
	m_commandBuffer.insertCmdErase(lba, size);
}

