#include "buffer_handler.h"

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

}

void CommandBufferHandler::writeBuffer(int lba, string value) {
	m_commandBuffer.insertCmd(lba, value);
}

void CommandBufferHandler::eraseBuffer(int lba, int size) {
	m_commandBuffer.insertCmd(lba, size);
}

CommandBuffer::CommandBuffer() {}

string CommandBuffer::readDataOnBuffer(int lba) {
	return "";
}

int CommandBuffer::getUsableBufferSize() {
	return 0;
}

void CommandBuffer::insertCmd(int lba, int size) {
}

void CommandBuffer::insertCmd(int lba, string value) {
}

