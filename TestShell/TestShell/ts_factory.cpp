#include "full_write_read_compare_ts.h"
#include "partial_lba_write_ts.h"
#include "write_read_aging_ts.h"
#include "erase_write_aging_ts.h"
#include "dll_main.h"
#include "cmd_factory.h"
#include "mock_ssd.h"
extern "C" LIB_API__ void registerTs(void)
{
	static FullWriteAndReadCompareTs fullWriteAndReadCompareTs;
	static PartialLbaWriteTs partialLbaWriteTs;
	static WriteReadAging writeReadAging;
	static EraseAndWriteAgingTs eraseWriteAging;
	static ::testing::NiceMock<MockSsd> mockSsd;
	CmdFactory::getInstance().setSdd(&mockSsd);


}

