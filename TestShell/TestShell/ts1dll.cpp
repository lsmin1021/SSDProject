#include "ts1dll.h"
#include "full_write_read_compare_ts.h"
AppCb cb;
static FullWriteAndReadCompareTs tsInstance;
extern "C" {
	DLL_API__ TsInterface* getInstance(AppCb* appCb) {
		cb = *appCb;
		return &tsInstance;
	}
}
