#pragma once

#ifdef MYLIBRARY_EXPORTS
#define LIB_API__ __declspec(dllexport)
#else
#define LIB_API__ __declspec(dllimport)
#endif

#include <vector>
#include <string>

using std::vector;
using std::string;

extern "C" {
	typedef bool (*ExcueteCmd) (const vector<string>& cmdTokens, const string& checkString);

	struct AppCb {
		ExcueteCmd excueteCmd;
	};
	typedef void (*OpenDll)(AppCb*);
	typedef void (*ExecuteTs)(const vector<string>& tsTokens);

	LIB_API__ void executeTs(const vector<string>& tsTokens);
	LIB_API__ void openDll(AppCb* appCb);
}


