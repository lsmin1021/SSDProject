#include <fstream>
#include <ostream>
#include <string>

using std::string;

class OutputHandler {
public:
	string read() {
		std::ifstream fs;
		string content;

		fs.open(FILE_NAME);

		fs >> content;

		fs.close();

		return content;
	}

	void write(string value) {
		std::ofstream fs;

		fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

		fs << value << std::endl;

		fs.close();
	}

private:
	const string FILE_NAME = "output.txt";
};