#include <string>

using std::string;

class FileHandler {
public:
	FileHandler() = default;
	virtual ~FileHandler() = default;
	virtual string read() = 0;
	virtual void write(string content) = 0;
};

class NandHandler : public FileHandler {
public:
	string read() {

	}

	void write(string content) {

	}

private:
	const string fileName = "ssd_nand.txt";
};

class OutputHandler : public FileHandler {
public:
	string read() {

	}

	void write(string content) {

	}

private:
	const string fileName = "output.txt";
};