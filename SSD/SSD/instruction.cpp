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