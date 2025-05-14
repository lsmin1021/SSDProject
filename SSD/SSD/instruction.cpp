#include "instruction.h"

Instruction& Instruction::setCmd(string cmd) {
	m_cmd = cmd;
	return *this;
}
Instruction& Instruction::setCmdWrite() {
	m_cmd = WRITE_CMD;
	return *this;
}
Instruction& Instruction::setCmdErase() {
	m_cmd = ERASE_CMD;
	return *this;
}
Instruction& Instruction::setValue(string value) {
	m_value = value;
	return *this;
}
Instruction& Instruction::setLba(int lba) {
	m_lba = lba;
	return *this;
}
Instruction& Instruction::setSize(int size) {
	m_size = size;
	return *this;
}

string Instruction::getCmd() { 
	return m_cmd; 
}
string Instruction::getValue() { 
	return m_value;
}
int Instruction::getLba() { 
	return m_lba;
}
int Instruction::getSize() { 
	return m_size; 
}

Instruction& Instruction::setInstString(const string& instStr) {
	m_cmd = instStr.substr(0, 1);

	string::size_type posLba = instStr.find('_', 2);
	m_lba = std::stoi(instStr.substr(2, posLba - 2));

	string::size_type posParam = posLba + 1;
	string param = instStr.substr(posParam);

	if (true == isWriteCommand()) { m_value = param; }
	else if (true == isEraseCommand()) { m_size = std::stoi(param); }

	return *this;
}

string Instruction::getInstString() {
	string ret = DELIMITER + m_cmd + DELIMITER + std::to_string(m_lba) + DELIMITER;
	if (WRITE_CMD == m_cmd) {
		ret += m_value;
	}
	else if (ERASE_CMD == m_cmd) {
		ret += std::to_string(m_size);
	}

	return ret;
}

bool Instruction::isWriteCommand() {
	if (WRITE_CMD == m_cmd) {
		return true;
	}
	return false;
}
bool Instruction::isEraseCommand() {
	if (ERASE_CMD == m_cmd) {
		return true;
	}
	return false;
}

void Instruction::show() {
	std::cout << m_cmd << ", " << m_value << ", " << m_lba << ", " << m_size << std::endl;
}