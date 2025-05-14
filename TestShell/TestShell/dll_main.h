#pragma once

#ifdef MYLIBRARY_EXPORTS
#define LIB_API__ __declspec(dllexport)
#else
#define LIB_API__ __declspec(dllimport)
#endif

extern "C" {
	typedef void (*OpenDll)(void);
	typedef void (*ExecuteTs)(const char*);
	typedef void (*ExcueteCmd) (int numArg, char* args[]);
	
	struct AppCb {

		ExcueteCmd excueteCmd;
	};

	LIB_API__ void executeTs(const char* tsName);
	LIB_API__ void openDll(void);
}


