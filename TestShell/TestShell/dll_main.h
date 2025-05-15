#pragma once

#ifdef MYLIBRARY_EXPORTS
#define LIB_API__ __declspec(dllexport)
#else
#define LIB_API__ __declspec(dllimport)
#endif

#include "dll.h"

extern "C" {

	typedef void (*OpenDll)(AppCb*);
	typedef void (*ExecuteTs)(const vector<string>& tsTokens);

	LIB_API__ void executeTs(const vector<string>& tsTokens);
	LIB_API__ void openDll(AppCb* appCb);
}


