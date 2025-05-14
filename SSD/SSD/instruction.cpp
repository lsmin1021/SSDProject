#include "instruction.h"

void Instruction::setCmd(string cmd) {
	m_cmd = cmd;
}
void Instruction::setValue(string value) { 
	m_value = value; 
}
void Instruction::setLba(int lba) { 
	m_lba = lba; 
}
void Instruction::setSize(int size) { 
	m_size = size; 
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