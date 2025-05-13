#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include "command_buffer.h"

namespace fs = std::filesystem;

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
	for (const auto& entry : fs::directory_iterator(DIR_NAME)) {
		if (fs::is_regular_file(entry)) {
			fs::remove(entry.path());
		}
	}

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME + "\\";

		if (i >= m_buffer.size()) {
			fileName.append(std::to_string(i)).append("_").append("empty");
		}
		else if ( "W" == m_buffer[i].getCmd() ) {
			fileName.append(std::to_string(i))
				.append("_W_")
				.append(std::to_string(m_buffer[i].getLba()))
				.append("_")
				.append(m_buffer[i].getValue());
		}
		else if ("E" == m_buffer[i].getCmd()) {
			fileName.append(std::to_string(i))
				.append("_E_")
				.append(std::to_string(m_buffer[i].getLba()))
				.append("_")
				.append(std::to_string(m_buffer[i].getSize()));
		}

		std::ofstream f(fileName);
		f.close();
	}
}

void CommandBuffer::setBufferDir() {
	fs::create_directory(DIR_NAME);

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME + "\\";

		fileName.append(std::to_string(i)).append("_empty");

		std::ofstream f(fileName);
		f.close();
	}
}

void CommandBuffer::loadBuffer() {
	for (const auto& entry : fs::directory_iterator(DIR_NAME)) {
		if (fs::is_regular_file(entry)) {
			loadBufferCmd(entry.path().filename().string());
		}
	}
}

void CommandBuffer::loadBufferCmd(string cmd) {
	string::size_type posCmdStart = cmd.find("_") + 1;
	string cmd_content = cmd.substr(posCmdStart);

	if (0 == cmd_content.compare("empty")) {
		return;
	}
	
	m_buffer.push_back(parseBufferCmd(cmd_content));
}

Buffer CommandBuffer::parseBufferCmd(string bufferCmd) {
	std::string cmd = bufferCmd.substr(0, 1);

	string::size_type posLba = bufferCmd.find('_', 2);
	string lba = bufferCmd.substr(2, posLba - 2);

	posLba += lba.length() - 1;
	string::size_type posParam = bufferCmd.find('_', posLba);
	string param = bufferCmd.substr(posLba, posParam - posLba);

	Buffer cb;
	cb.setCmd(cmd);
	cb.setLba(std::stoi(lba));
	
	if ("W" == cmd) {cb.setValue(param);}
	else if ("E" == cmd) { cb.setSize(std::stoi(param)); }

	std::cout << cmd << ", " << lba << ", " << param << std::endl;

	return cb;
}

bool CommandBuffer::isDirectoryExist() {
	if (fs::exists(DIR_NAME) && fs::is_directory(DIR_NAME)) {
		return true;
	}

	return false;
}
