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
int Instruction::getLbaTo() {
	return m_lba + m_size - 1;
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

bool Instruction::canIgnoreCommand(Instruction& target, Instruction& base) {
	if (true == base.isWriteCommand()) {
		if (true == target.isWriteCommand() && target.getLba() == base.getLba()) {
			return true;
		}
		else if (true == target.isEraseCommand() && target.getLba() == base.getLba() && target.getSize() == 1) {
			return true;
		}
	}
	else if (true == base.isEraseCommand()) {
		if (true == target.isWriteCommand() && base.getLba() <= target.getLba() && base.getLbaTo() >= target.getLba()) {
			return true;
		}
		else if (true == base.isEraseCommand() && base.getLba() <= target.getLba() && base.getLbaTo() >= target.getLbaTo()) {
			return true;
		}
	}

	return false;
}

bool Instruction::isMergeable(Instruction& inst1, Instruction& inst2) {
	if (true == inst1.isWriteCommand() || true == inst2.isWriteCommand()) return false;

	int lbaFrom1 = inst1.getLba();
	int lbaTo1 = inst1.getLbaTo();
	int lbaFrom2 = inst2.getLba();
	int lbaTo2 = inst2.getLbaTo();

	if (lbaFrom1 <= lbaTo2 && lbaFrom2 <= lbaTo1) {
		return true;
	}

	if (lbaTo1 + 1 == lbaFrom2 || lbaTo2 + 1 == lbaFrom1) {
		return true;
	}

	return false;
}

Instruction Instruction::mergeInst(Instruction& inst1, Instruction& inst2) {
	int lbaFrom = inst1.getLba() < inst2.getLba() ? inst1.getLba() : inst2.getLba();
	int lbaTo = inst1.getLbaTo() > inst2.getLbaTo() ? inst1.getLbaTo() : inst2.getLbaTo();

	int size = lbaTo - lbaFrom + 1;

	return Instruction().setCmdErase().setLba(lbaFrom).setSize(size);
}

void Instruction::show() {
	std::cout << m_cmd << ", " << m_value << ", " << m_lba << ", " << m_size << std::endl;
}