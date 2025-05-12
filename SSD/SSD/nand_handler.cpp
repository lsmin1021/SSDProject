#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <map>

using std::string;
using std::map;


class NandHandler {
public:
	virtual void read() {
		string ssdDataStr = readNand();
		m_ssdData = getSSDData(ssdDataStr);
	}

	virtual string getData(int lba) {
		if (m_ssdData.find(lba) == m_ssdData.end()) {
			return EMPTY_VALUE;
		}

		return m_ssdData[lba];
	}

	virtual void write(int lba, string value) {
		
		if (m_ssdData.find(lba) == m_ssdData.end()) {
			m_ssdData.insert(std::make_pair(lba, value));
		}
		else {
			m_ssdData[lba] = value;
		}

		writeDataToSSD();
	}

private:
	map<int, string> getSSDData(string ssdDataStr) {
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

	string readNand() {
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

	void writeDataToSSD() {
		std::ofstream fs;

		fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

		for (auto d : m_ssdData) {
			fs << std::to_string(d.first) << " " << d.second << std::endl;
		}

		fs.close();
	}

	map<int, string> m_ssdData;
	const string FILE_NAME = "ssd_nand.txt";
	const string EMPTY_VALUE = "0x00000000";
};
