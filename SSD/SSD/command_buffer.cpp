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

	for (int i = m_buffer.size() - 1; i >= 0; i--) {
		Instruction& preCmd = m_buffer[i];

		if (true == cmd.isWriteCommand()) {
			if (true == preCmd.isWriteCommand() && preCmd.getLba() == cmd.getLba()) {
				m_buffer.erase(m_buffer.begin() + i);
			}
			else if (true == preCmd.isEraseCommand() && preCmd.getLba() == cmd.getLba() && preCmd.getSize() == 1) {
				m_buffer.erase(m_buffer.begin() + i);
			}
		}
		else if (true == cmd.isEraseCommand()) {
			if (true == preCmd.isWriteCommand() && cmd.getLba() <= preCmd.getLba() && cmd.getLbaTo() >= preCmd.getLba()) {
				m_buffer.erase(m_buffer.begin() + i);
			}
			else if (true == cmd.isEraseCommand() && cmd.getLba() <= preCmd.getLba() && cmd.getLbaTo() >= preCmd.getLbaTo()) {
				m_buffer.erase(m_buffer.begin() + i);
			}
		}
	}
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

	vector<int> writeLbaList;
	for (int i = m_buffer.size() - 1; i >= 0; i--) {
		Instruction& targetInst = m_buffer[i];

		if (true == targetInst.isWriteCommand()) {
			writeLbaList.push_back(targetInst.getLba());
			continue;
		}
		if (true == isConflicted(targetInst, writeLbaList)) {
			continue;
		}

		if (true == Instruction::isMergeable(latestInst, targetInst)) {
			latestInst = Instruction::mergeInst(latestInst, targetInst);

			m_buffer.erase(m_buffer.begin() + i);
		}
	}

	insertMergedInst(latestInst);
}

bool CommandBuffer::isConflicted(Instruction& targetInst, vector<int>& writeLbaList) {
	bool ret = false;
	for (int lba : writeLbaList) {
		if (targetInst.getLba() <= lba && targetInst.getLbaTo() >= lba) {
			ret = true;
		}
	}

	return ret;
}

void CommandBuffer::insertMergedInst(Instruction& mergedInst) {
	while (MAX_ERASE_SIZE < mergedInst.getSize()) {
		m_buffer.push_back(Instruction().setCmdErase().setLba(mergedInst.getLba()).setSize(MAX_ERASE_SIZE));

		mergedInst.setLba(mergedInst.getLba() + MAX_ERASE_SIZE);
		mergedInst.setSize(mergedInst.getSize() - MAX_ERASE_SIZE);
	}

	m_buffer.push_back(mergedInst);
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
			if (cmd.getLba() <= lba && cmd.getLbaTo() >= lba) {
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
		string fileName = DIR_NAME + "\\" + std::to_string(i) + "_" + EMPTY_CMD;
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