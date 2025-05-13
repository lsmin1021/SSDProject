#pragma once
#include <fstream>
#include <ostream>
#include <string>

using std::string;

class OutputInterface {
public:
	virtual void write(string value) = 0;
};

class OutputHandler : public OutputInterface {
public:
	static OutputHandler& getInstance();
	void write(string value) override;

private:
	OutputHandler();

	const string FILE_NAME = "ssd_output.txt";
};