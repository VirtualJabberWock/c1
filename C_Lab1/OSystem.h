#pragma once

#include <inttypes.h>
#include "DebugUtils.h"

#define isWindows(os) ((os == "Windows") || (os == "Windows 64-bit"))
#define isLinux(os) (os == "Linux")

#ifdef _WIN32
#define WINVER 0x0501
#define _WIN32_WINNT WINVER
#include <windows.h>
#include <sys\stat.h>
#endif

#ifdef __linux__
#define "TODO"
#endif

const char* __os__();
int64_t getFileSize(const char* file_name);





