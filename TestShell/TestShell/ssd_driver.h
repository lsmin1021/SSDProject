#pragma once
#include <cstdlib>  
#include "ssd_interface.h"
#include "shell_excuter.h"

class SsdDriver : public SsdInterface {
public:
	SsdDriver(ShellExecutorInterface* exec) : m_executor(exec) {}
	~SsdDriver() override = default;
	void readData(const string& lba) override;
	void writeData(const string& lba, const string& data) override;
	void eraseData(const string& lba, const string& size) override;
	void eraseDataRange(const string& StartLba, const string& endLba) override;

private:
	const string WRITE_CMD = "SSD W ";
	const string READ_CMD = "SSD R ";
	const string ERASE_CMD = "SSD E ";
	ShellExecutorInterface* m_executor;
};