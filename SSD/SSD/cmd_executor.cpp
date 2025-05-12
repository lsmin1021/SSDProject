
#include <iostream>

#include "output_handler.cpp"
#include "nand_handler.cpp"

class CmdExecutor {
public:
	CmdExecutor() {
		m_nandHandler = new NandHandler();
		m_outputHandler = new OutputHandler();
	}

	virtual string read(int lba) {
		string ret = readDataOnAddr(lba);

		m_outputHandler->write(ret);

		return ret;
	}

	virtual void write(int lba, string value) {
		writeDataOnAddr(lba, value);
	}

	void setError() {
		m_outputHandler->write("ERROR");
	}
	
	void setNandHandler(NandInterface* handler) {
		m_nandHandler = handler;
	}

	void setOutputHandler(OutputInterface* handler) {
		m_outputHandler = handler;
	}

private:
	string readDataOnAddr(int lba) {
		m_nandHandler->read();

		return m_nandHandler->getData(lba);
	}

	void writeDataOnAddr(int lba, string value) {
		m_nandHandler->read();

		m_nandHandler->write(lba, value);
	}

	NandInterface* m_nandHandler;
	OutputInterface* m_outputHandler;
};
