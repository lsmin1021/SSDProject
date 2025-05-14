#include <iostream>
#include <filesystem>
#include <fstream>
#include "command_buffer.h"

namespace fs = std::filesystem;

CommandBuffer::CommandBuffer() {
	loadBuffer();
}

string CommandBuffer::readData(int lba) {
	return getValueOnBuffer(lba);
}

void CommandBuffer::insertCmd(Instruction cmd) {
	ignoreCommand(cmd);
	m_buffer.push_back(cmd);

	mergeCommand();

	storeDataToBuffer();
}

void CommandBuffer::mergeCommand() {
	if (true == m_buffer.empty()) {
		return;
	}

	if (true == m_buffer.back().isWriteCommand()) {
		return;
	}

	Instruction latestInst = m_buffer.back();
	m_buffer.pop_back();

	for (int i = m_buffer.size() - 1; i >= 0; i--) {
		Instruction& targetInst = m_buffer[i];

		if (true == targetInst.isWriteCommand()) {
			break;
		}

		if (true == isMergeable(latestInst, targetInst)) {
			latestInst = merge(latestInst, targetInst);

			m_buffer.erase(m_buffer.begin() + i);
		}

		latestInst.show();
	}

	while (MAX_ERASE_SIZE < latestInst.getSize()) {
		m_buffer.push_back(Instruction().setCmdErase().setLba(latestInst.getLba()).setSize(MAX_ERASE_SIZE));

		latestInst.setLba(latestInst.getLba() + MAX_ERASE_SIZE);
		latestInst.setSize(latestInst.getSize() - MAX_ERASE_SIZE);
	}

	m_buffer.push_back(latestInst);
}

Instruction CommandBuffer::merge(Instruction& inst1, Instruction& inst2) {
	int lbaFrom = inst1.getLba() < inst2.getLba() ? inst1.getLba() : inst2.getLba();

	int lbaTo1 = inst1.getLba() + inst1.getSize() - 1;
	int lbaTo2 = inst2.getLba() + inst2.getSize() - 1;
	int lbaTo = lbaTo1 > lbaTo2 ? lbaTo1 : lbaTo2;

	int size = lbaTo - lbaFrom + 1;
	
	return Instruction().setCmdErase().setLba(lbaFrom).setSize(size);
}

bool CommandBuffer::isMergeable(Instruction& inst1, Instruction& inst2) {
	int lbaFrom1 = inst1.getLba();
	int lbaTo1 = lbaFrom1 + inst1.getSize() - 1;
	int lbaFrom2 = inst2.getLba();
	int lbaTo2 = lbaFrom2 + inst2.getSize() - 1;

	if (lbaFrom1 <= lbaTo2 && lbaFrom2 <= lbaTo1) {
		return true;
	}
	
	if (lbaTo1 + 1 == lbaFrom2 || lbaTo2 + 1 == lbaFrom1) {
		return true;
	}

	return false;
}

vector<Instruction> CommandBuffer::getBufferCommands() {
	return m_buffer;
}

bool CommandBuffer::isFull() {
	if (MAX_BUFFER_SIZE <= m_buffer.size()) {
		return true;
	}

	return false;
}

void CommandBuffer::clear() {
	m_buffer.clear();

	storeDataToBuffer();
}

void CommandBuffer::loadBuffer() {
	if (false == FileHandler::isDirectoryExist(DIR_NAME)) {
		setBufferDir();
		return;
	}

	vector<string> fileList = FileHandler::getFileList(DIR_NAME);
	for (string fileName : fileList) {
		loadBufferCmd(fileName);
	}
}

void CommandBuffer::ignoreCommand(Instruction& cmd) {
	if (true == m_buffer.empty()) return;

	if (true == cmd.isWriteCommand()) {
		for (int i = m_buffer.size() - 1; i >= 0; i--) {
			Instruction& preCmd = m_buffer[i];

			if (true == preCmd.isWriteCommand()) {
				if (preCmd.getLba() == cmd.getLba()) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
			else if (true == preCmd.isEraseCommand()) {
				if (preCmd.getLba() == cmd.getLba() && preCmd.getSize() == 1) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
		}
	}
	else if (true == cmd.isEraseCommand()) {
		for (int i = m_buffer.size() - 1; i >= 0; i--) {
			Instruction& preCmd = m_buffer[i];

			if (true == preCmd.isWriteCommand()) {
				if (cmd.getSize() != 0 &&
					cmd.getLba() <= preCmd.getLba() &&
					cmd.getLba() + cmd.getSize() > preCmd.getLba()) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
			else if (true == cmd.isEraseCommand()) {
				if (cmd.getSize() != 0 &&
					cmd.getLba() <= preCmd.getLba() &&
					cmd.getSize() + cmd.getLba() >= preCmd.getLba() + preCmd.getSize()) {
					m_buffer.erase(m_buffer.begin() + i);
				}
			}
		}
	}
}

string CommandBuffer::getValueOnBuffer(int lba) {
	string value = "";

	for (Instruction cmd : m_buffer) {
		if (true == cmd.isWriteCommand()) {
			if (cmd.getLba() == lba) {
				value = cmd.getValue();
			}
		}
		else if (true == cmd.isEraseCommand()) {
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
	FileHandler::clearDir(DIR_NAME);

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME + "\\" + std::to_string(i);

		if (i >= m_buffer.size()) {
			fileName.append("_").append(EMPTY_CMD);
		}
		else {
			fileName += m_buffer[i].getInstString();
		}

		FileHandler::makeFile(fileName);
	}
}

void CommandBuffer::setBufferDir() {
	fs::create_directory(DIR_NAME);

	for (int i = 0; i < 5; i++) {
		string fileName = DIR_NAME + "\\" + std::to_string(i);

		fileName.append("_").append(EMPTY_CMD);

		FileHandler::makeFile(fileName);
	}
}

void CommandBuffer::loadBufferCmd(string cmd) {
	string::size_type posCmdStart = cmd.find("_") + 1;
	string cmd_content = cmd.substr(posCmdStart);

	if (0 == cmd_content.compare(EMPTY_CMD)) {
		return;
	}

	m_buffer.push_back(Instruction().setInstString(cmd_content));
}

bool FileHandler::isDirectoryExist(const string& dir) {
	if (fs::exists(dir) && fs::is_directory(dir)) {
		return true;
	}

	return false;
}

void FileHandler::clearDir(const string& dir) {
	for (const auto& entry : fs::directory_iterator(dir)) {
		if (fs::is_regular_file(entry)) {
			fs::remove(entry.path());
		}
	}
}

void FileHandler::makeFile(string path) {
	std::ofstream f(path);
	f.close();
}

vector<string> FileHandler::getFileList(string dir) {
	vector<string> ret;

	for (const auto& entry : fs::directory_iterator(dir)) {
		if (fs::is_regular_file(entry)) {
			ret.push_back(entry.path().filename().string());
		}
	}

	return ret;
}