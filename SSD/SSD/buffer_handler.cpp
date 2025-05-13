#include "buffer_handler.h"

CommandBufferHandler& CommandBufferHandler::getInstance() {
	static CommandBufferHandler instance;

	return instance;
}

string CommandBufferHandler::readBuffer(int lba) {
	return "";
}

bool CommandBufferHandler::isFull() {
	return false;
}

void CommandBufferHandler::flush() {

}

void CommandBufferHandler::writeBuffer(int lba, string value) {

}

void CommandBufferHandler::eraseBuffer(int lba, int size) {

}

CommandBuffer::CommandBuffer() {}

string CommandBuffer::readDataOnBuffer(int lba) {
	return "";
}

int CommandBuffer::getUsableBufferSize() {
	return 0;
}

int CommandBuffer::insertCmd(int lba, int size) {
	return 0;
}

int CommandBuffer::insertCmd(int lba, string value) {
	return 0;
}

