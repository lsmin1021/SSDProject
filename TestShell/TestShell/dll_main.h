#pragma once

#ifdef MYLIBRARY_EXPORTS
#define LIB_API__ __declspec(dllexport)
#else
#define LIB_API__ __declspec(dllimport)
#endif

extern "C" LIB_API__ void executeTs(const char* tsName);
extern "C" LIB_API__ void registerTs(void);
