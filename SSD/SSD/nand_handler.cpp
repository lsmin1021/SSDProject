#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <map>

using std::string;
using std::map;

class FileHandler {
public:
	FileHandler() = default;
	virtual ~FileHandler() = default;
	virtual string read() = 0;
	virtual void write(string content) = 0;
};

class NandHandler {
public:
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

		fs.open("ssd_nand.txt");

		string line;
		while (getline(fs, line)) {
			content.append(line).append("\n");
		}

		fs.close();

		return content;
	}

	void writeNand(map<int, string> ssdData) {
		std::ofstream fs;

		fs.open("ssd_nand.txt", std::ofstream::out | std::ofstream::trunc);

		for (auto d : ssdData) {
			fs << std::to_string(d.first) << " " << d.second << std::endl;
		}

		fs.close();
	}

private:
	const string fileName = "ssd_nand.txt";
};

/*
class OutputHandler : public FileHandler {
public:
	string read() {

	}

	void write(string content) {

	}

private:
	const string fileName = "output.txt";
};
*/