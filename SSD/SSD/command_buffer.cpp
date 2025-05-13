#include <iostream>
#include <Windows.h>
#include "command_buffer.h"

using namespace std;

CommandBuffer::CommandBuffer() {
	if (false == isDirectoryExist()) {
		setBufferDir();
	}

	loadBuffer();
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

void CommandBuffer::loadBuffer() {
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(DIR_SEARCH_PATTERN.c_str(), &findFileData);

	do {
		if (std::string(findFileData.cFileName) == "." || 
			std::string(findFileData.cFileName) == "..") {
			continue;
		}

		loadBufferCmd(findFileData.cFileName);
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind); // ÇÚµé ´Ý±â
}

void CommandBuffer::loadBufferCmd(string cmd) {
	string::size_type posCmdStart = cmd.find("_") + 1;
	string cmd_content = cmd.substr(posCmdStart, cmd.find(".") - posCmdStart);

	if (0 == cmd_content.compare("empty")) {
		return;
	}
	// TODO
}

bool CommandBuffer::isDirectoryExist() {
	DWORD ftyp = GetFileAttributesA(DIR_NAME.c_str());

	if (ftyp == FILE_ATTRIBUTE_DIRECTORY) {
		return true;
	}

	return false;
}
