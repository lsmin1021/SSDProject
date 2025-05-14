#pragma once

#ifdef MYLIBRARY_EXPORTS
#define LIB_API__ __declspec(dllexport)
#else
#define LIB_API__ __declspec(dllimport)
#endif

extern "C" {
	typedef bool (*ExcueteCmd) (int numToken, char* tokens[]);

	struct AppCb {
		ExcueteCmd excueteCmd;
	};
	typedef void (*OpenDll)(AppCb*);
	typedef void (*ExecuteTs)(const char*);

	LIB_API__ void executeTs(const char* tsName);
	LIB_API__ void openDll(AppCb* appCb);
}


