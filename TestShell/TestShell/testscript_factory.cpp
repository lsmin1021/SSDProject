#include "testscript_factory.h"

#include "full_write_read_compare_ts.h"
#include "partial_lba_write_ts.h"
#include "write_read_aging_ts.h"
#include "erase_write_aging_ts.h"
#include "ssd_interface.h"
#include "dll_main.h"
static FullWriteAndReadCompareTs fullWriteAndReadCompareTs;
static PartialLbaWriteTs partialLbaWriteTs;
static WriteReadAging writeReadAging;
static EraseAndWriteAgingTs eraseWriteAging;

void TestScriptFactory::generateTs(void)
{
	static FullWriteAndReadCompareTs fullWriteAndReadCompareTs;
	static PartialLbaWriteTs partialLbaWriteTs;
	static WriteReadAging writeReadAging;
	static EraseAndWriteAgingTs eraseWriteAging;
}

TestScriptFactory& TestScriptFactory::getInstance()
{
	static TestScriptFactory instance;
	return instance;
}

TsInterface* TestScriptFactory::getTs(const string& name) const {
	for (auto& cmd : m_supportedTs) {
		vector<string> names = cmd->getName();
		for (auto myName : names) {
			if (name == myName) {
				return cmd;
			}
		}
	}
	throw std::invalid_argument("Invalid command: " + name);
}
