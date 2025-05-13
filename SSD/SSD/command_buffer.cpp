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

	storeDataToBuffer();
}

void CommandBuffer::insertCmd(int lba, int size) {
	m_buffer.push_back(Buffer("E", "", lba, size));

	storeDataToBuffer();
}

void CommandBuffer::clear() {
	m_buffer.clear();

	storeDataToBuffer();
}

void CommandBuffer::storeDataToBuffer() {
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(DIR_SEARCH_PATTERN.c_str(), &findFileData);

	do {
		if (std::string(findFileData.cFileName) == "." ||
			std::string(findFileData.cFileName) == "..") {
			continue;
		}

		string delFileName = DIR_NAME + "\\";
		delFileName.append(findFileData.cFileName);

		DeleteFileA(delFileName.c_str());
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME;

		if (i >= m_buffer.size()) {
			fileName.append("\\").append(std::to_string(i)).append("_").append("empty");
		}
		else if ( "W" == m_buffer[i].getCmd() ) {
			fileName.append("\\")
				.append(std::to_string(i))
				.append("_W_")
				.append(std::to_string(m_buffer[i].getLba()))
				.append("_")
				.append(m_buffer[i].getValue());
		}
		else if ("E" == m_buffer[i].getCmd()) {
			fileName.append("\\")
				.append(std::to_string(i))
				.append("_W_")
				.append(std::to_string(m_buffer[i].getLba()))
				.append("_")
				.append(std::to_string(m_buffer[i].getSize()));
		}
		HANDLE hFile = CreateFileA(fileName.c_str(), GENERIC_ALL, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		CloseHandle(hFile);
	}
}

void CommandBuffer::setBufferDir() {
	bool ret = CreateDirectoryA(DIR_NAME.data(), NULL);

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME;

		fileName.append("\\").append(std::to_string(i)).append("_").append("empty");

		HANDLE hFile = CreateFileA(fileName.c_str(), GENERIC_ALL, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		CloseHandle(hFile);
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

	FindClose(hFind);
}

void CommandBuffer::loadBufferCmd(string cmd) {
	string::size_type posCmdStart = cmd.find("_") + 1;
	string cmd_content = cmd.substr(posCmdStart);

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
