#include "nand_storage.h"

NandStorage::NandStorage() {
	m_storage = getSSDData(readNand());
}

string NandStorage::read(int lba) {
	if (m_storage.find(lba) == m_storage.end()) {
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

	storeDataToSSD();
}

void NandStorage::erase(int lba, int cnt) {
	for (int i = 0; i < cnt; i++) {
		int targetIndex = lba + i;
		if (99 < targetIndex) {
			break;
		}

		if (true == isEmptyLBA(targetIndex)) {
			continue;
		}

		m_storage.erase(targetIndex);
	}

	storeDataToSSD();
}

bool NandStorage::isEmptyLBA(int lba) {
	if (m_storage.find(lba) == m_storage.end()) {
		return true;
	}

	return false;
}

map<int, string> NandStorage::getSSDData(string ssdDataStr) {
	map<int, string> ret;
	std::istringstream iss(ssdDataStr);
	string line;

	while (std::getline(iss, line)) {
		int lba = std::stoi(line.substr(0, line.find(" ")));
		string value = line.substr(line.find(" ") + 1);

		ret.insert(std::make_pair(lba, value));
	}

	return ret;
}

string NandStorage::readNand() {
	std::ifstream fs;
	string content;

	fs.open(FILE_NAME);

	string line;
	while (getline(fs, line)) {
		content.append(line).append("\n");
	}

	fs.close();

	return content;
}

void NandStorage::storeDataToSSD() {
	std::ofstream fs;

	fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

	for (auto d : m_storage) {
		fs << std::to_string(d.first) << " " << d.second << std::endl;
	}

	fs.close();
}