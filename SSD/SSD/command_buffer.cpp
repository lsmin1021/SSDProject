#include <Windows.h>
#include "command_buffer.h"

using namespace std;

CommandBuffer::CommandBuffer() {
	if (false == isDirectoryExist()) {
		setBufferDir();
	}
}

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

void CommandBuffer::setBufferDir() {
	bool ret = CreateDirectoryA(DIR_NAME.data(), NULL);

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME;

		fileName.append("\\").append(std::to_string(i)).append("_").append("empty.txt");

		HANDLE hFile = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	}
}

bool CommandBuffer::isDirectoryExist() {
	DWORD ftyp = GetFileAttributesA(DIR_NAME.c_str());

	if (ftyp == FILE_ATTRIBUTE_DIRECTORY) {
		return true;
	}

	return false;
}
