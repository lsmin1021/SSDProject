#include "testscript_factory.h"

#include "full_write_read_compare_ts.h"
#include "partial_lba_write_ts.h"
#include "write_read_aging_ts.h"
#include "erase_write_aging_ts.h"
#include "ssd_interface.h"
#include "dll_main.h"
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

TsInterface* TestScriptFactory::getTs(const string& tsName) const {
	for (auto ts : m_supportedTs) {
		if (tsName == ts->getName() || tsName == ts->getShortCutName()) return ts;
	}
	throw std::invalid_argument("Invalid command: " + tsName);
}
