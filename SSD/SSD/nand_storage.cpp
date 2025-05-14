#include "nand_storage.h"

NandStorage::NandStorage() {
	loadData();
}

string NandStorage::read(int lba) {
	if (true == isEmptyLBA(lba)) {
		return EMPTY_VALUE;
	}

	return m_storage[lba];
}

void NandStorage::write(int lba, string value) {
	if (true == isEmptyLBA(lba)) {
		m_storage.insert(std::make_pair(lba, value));
	}
	else {
		m_storage[lba] = value;
	}

	storeData();
}

void NandStorage::erase(int lba, int cnt) {
	for (int targetLba = lba; targetLba < lba + cnt && targetLba <= MAX_LBA; targetLba++) {
		if (true == isEmptyLBA(targetLba)) {
			return;
		}

		m_storage.erase(targetLba);
	}

	storeData();
}

bool NandStorage::isEmptyLBA(int lba) {
	if (m_storage.find(lba) == m_storage.end()) {
		return true;
	}

	return false;
}

void NandStorage::loadData() {
	convertDataFile(loadDataFile());
}

void NandStorage::storeData() {
	std::ofstream fs;

	fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

	for (auto d : m_storage) {
		fs << std::to_string(d.first) << " " << d.second << std::endl;
	}

	fs.close();
}

string NandStorage::loadDataFile() {
	string content;
	std::ifstream fs;

	fs.open(FILE_NAME);

	string line;
	while (getline(fs, line)) {
		content.append(line).append("\n");
	}

	fs.close();

	return content;
}

void NandStorage::convertDataFile(string content) {
	std::istringstream iss(content);

	string line;
	while (std::getline(iss, line)) {
		int lba = std::stoi(line.substr(0, line.find(" ")));
		string value = line.substr(line.find(" ") + 1);

		m_storage.insert(std::make_pair(lba, value));
	}
}
