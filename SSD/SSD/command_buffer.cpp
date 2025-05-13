#include "command_buffer.h"

CommandBuffer::CommandBuffer() {}

string CommandBuffer::readDataOnBuffer(int lba) {
	return "";
}

vector<Buffer> CommandBuffer::getBufferCommands() {
	return m_buffer;
}

int CommandBuffer::getUsableBufferSize() {
	return m_buffer.size();
}

void CommandBuffer::insertCmd(int lba, string value) {
	m_buffer.push_back(Buffer("W", value, lba, 0));
}

void CommandBuffer::insertCmd(int lba, int size) {
	m_buffer.push_back(Buffer("E", "", lba, size));
}

void CommandBuffer::clear() {
	m_buffer.clear();
}