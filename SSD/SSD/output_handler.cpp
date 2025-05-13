#include "output_handler.h"


OutputHandler::OutputHandler() {}

OutputHandler& OutputHandler::getInstance() {
	static OutputHandler instance;
		
	return instance;
}

void OutputHandler::write(string value)  {
	std::ofstream fs;

	fs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);

	fs << value << std::endl;

	fs.close();
}

