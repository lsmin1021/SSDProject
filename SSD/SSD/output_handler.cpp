#include <fstream>
#include <ostream>
#include <string>

using std::string;

class OutputInterface {
public:
	virtual string read() = 0;
	virtual void write(string value) = 0;
};

class OutputHandler : public OutputInterface{
public:
	string read() override {
		std::ifstream fs;
		string content;

		fs.open(FILE_NAME);

		fs >> content;

		fs.close();

		return content;
	}

	void write(string value) override {
		std::ofstream fs;

		fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

		fs << value << std::endl;

		fs.close();
	}

private:
	const string FILE_NAME = "output.txt";
};