#pragma once

#ifdef TSLIB_EXPORTS
#define DLL_API__ __declspec(dllexport)
#else
#define DLL_API__ __declspec(dllimport)
#endif

#include <vector>
#include "testscript_interface.h"
extern "C" {
	typedef TsInterface* (*GetInstance)(AppCb*);
	DLL_API__ TsInterface* getInstance(AppCb* appCb);
}