#include <iostream>
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
	return getValueOnBuffer(lba);
}

vector<Buffer> CommandBuffer::getBufferCommands() {
	return m_buffer;
}

int CommandBuffer::getUsableBufferSize() {
	return m_buffer.size();
}

void CommandBuffer::insertCmdWrite(int lba, string value) {
	Buffer cmd(WRITE_CMD, value, lba, 0);

	ignoreCommand(cmd);
	m_buffer.push_back(cmd);
	
	storeDataToBuffer();
}

void CommandBuffer::insertCmdErase(int lba, int size) {
	Buffer cmd(ERASE_CMD, "", lba, size);

	ignoreCommand(cmd);
	m_buffer.push_back(cmd);

	storeDataToBuffer();
}

void CommandBuffer::ignoreCommand(Buffer& cmd) {
	if (true == m_buffer.empty()) return;

	if (WRITE_CMD == cmd.getCmd()) {
		for (int i = m_buffer.size() - 1; i >= 0; i--) {
			Buffer& preCmd = m_buffer[i];

			if (WRITE_CMD == preCmd.getCmd()) {
				if (preCmd.getLba() == cmd.getLba()) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
			else if (ERASE_CMD == preCmd.getCmd()) {
				if (preCmd.getLba() == cmd.getLba() && preCmd.getSize() == 1) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
		}
	}
	else if (ERASE_CMD == cmd.getCmd()) {
		for (int i = m_buffer.size() - 1; i >= 0; i--) {
			Buffer& preCmd = m_buffer[i];

			if (WRITE_CMD == preCmd.getCmd()) {
				if (cmd.getSize() != 0 &&
					cmd.getLba() <= preCmd.getLba() &&
					cmd.getLba() + cmd.getSize() > preCmd.getLba()) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
			else if (ERASE_CMD == preCmd.getCmd()) {
				if (cmd.getSize() != 0 &&
					cmd.getLba() <= preCmd.getLba() &&
					cmd.getSize() + cmd.getLba() >= preCmd.getLba() + preCmd.getSize()) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
		}
	}
}

void CommandBuffer::clear() {
	m_buffer.clear();

	storeDataToBuffer();
}

string CommandBuffer::getValueOnBuffer(int lba) {
	string value = "";

	for (Buffer cmd : m_buffer) {
		if (WRITE_CMD == cmd.getCmd()) {
			if (cmd.getLba() == lba) {
				value = cmd.getValue();
			}
		}
		else if (ERASE_CMD == cmd.getCmd()) {
			if (0 < cmd.getSize() &&
				cmd.getLba() <= lba &&
				cmd.getLba() + cmd.getSize() > lba) {
				value = EMPTY_VALUE;
			}
		}
	}

	return value;
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
			fileName.append(std::to_string(i)).append("_").append(EMPTY_CMD);
		}
		else {
			fileName.append(makeBufferCmd(i, m_buffer[i]));
		}	

		std::ofstream f(fileName);
		f.close();
	}
}

void CommandBuffer::setBufferDir() {
	fs::create_directory(DIR_NAME);

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME + "\\";

		fileName.append(std::to_string(i)).append("_").append(EMPTY_CMD);

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

	if (0 == cmd_content.compare(EMPTY_CMD)) {
		return;
	}

	m_buffer.push_back(parseBufferCmd(cmd_content));
}

Buffer CommandBuffer::parseBufferCmd(string bufferCmd) {
	std::string cmd = bufferCmd.substr(0, 1);

	string::size_type posLba = bufferCmd.find('_', 2);
	string lba = bufferCmd.substr(2, posLba - 2);

	string::size_type posParam = posLba + 1;
	string param = bufferCmd.substr(posParam);

	Buffer cb;
	cb.setCmd(cmd);
	cb.setLba(std::stoi(lba));
	
	if (WRITE_CMD == cmd) {cb.setValue(param);}
	else if (ERASE_CMD == cmd) { cb.setSize(std::stoi(param)); }

	return cb;
}

string CommandBuffer::makeBufferCmd(int index, Buffer& bufferCmd) {
	string ret = "";

	ret.append(std::to_string(index)).append("_");
	ret.append(bufferCmd.getCmd()).append("_");
	ret.append(std::to_string(bufferCmd.getLba())).append("_");

	if (WRITE_CMD == bufferCmd.getCmd()) { ret.append(bufferCmd.getValue()); }
	else if (ERASE_CMD == bufferCmd.getCmd()) { ret.append(std::to_string(bufferCmd.getSize())); }

	return ret;
}

bool CommandBuffer::isDirectoryExist() {
	if (fs::exists(DIR_NAME) && fs::is_directory(DIR_NAME)) {
		return true;
	}

	return false;
}
