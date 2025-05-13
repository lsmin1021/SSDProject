#include <fstream>
#include <ostream>
#include <string>

using std::string;

class OutputInterface {
public:
	virtual void write(string value) = 0;
};

class OutputHandler : public OutputInterface{
public:
	static OutputHandler& getInstance() {
		static OutputHandler instance;
		
		return instance;
	}

	void write(string value) override {
		std::ofstream fs;

		fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

		fs << value << std::endl;

		fs.close();
	}

private:
	OutputHandler() {}

	const string FILE_NAME = "ssd_output.txt";
};