#pragma once

#include <vector>
#include <string>

#ifdef TSLIB_EXPORTS 
#define DLL_API__ __declspec(dllexport)
#else
#define DLL_API__ __declspec(dllimport)
#endif

using std::vector;
using std::string;
typedef bool (*ExcueteCmd) (const vector<string>& cmdTokens, const string& checkString);

struct AppCb {
	ExcueteCmd excueteCmd;
};

class TsInterface;
typedef TsInterface* (*GetInstance)(AppCb*);
extern "C" DLL_API__ TsInterface* getInstance(AppCb* appCb);