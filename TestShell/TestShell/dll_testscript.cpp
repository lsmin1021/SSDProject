
#include "testscript_interface.h"

extern "C" {
	DLL_API__ TsInterface* getInstance(AppCb* appCb) {
		return TsInterface::getInstance(appCb);
	}
}

