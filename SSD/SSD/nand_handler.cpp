#include "nand_handler.h"

NandHandler::NandHandler() {
	m_ssdData = getSSDData(readNand());
}

string NandHandler::read(int lba) {
	if (m_ssdData.find(lba) == m_ssdData.end()) {
		return EMPTY_VALUE;
	}

	return m_ssdData[lba];
}

void NandHandler::write(int lba, string value) {
		
	if (m_ssdData.find(lba) == m_ssdData.end()) {
		m_ssdData.insert(std::make_pair(lba, value));
	}
	else {
		m_ssdData[lba] = value;
	}

	writeDataToSSD();
}

map<int, string> NandHandler::getSSDData(string ssdDataStr) {
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

string NandHandler::readNand() {
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

void NandHandler::writeDataToSSD() {
	std::ofstream fs;

	fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

	for (auto d : m_ssdData) {
		fs << std::to_string(d.first) << " " << d.second << std::endl;
	}

	fs.close();
}