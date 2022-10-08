#include "OSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

LPWSTR CharToLPWSTR(LPCSTR char_string)
{
	LPWSTR res;
	DWORD res_len = MultiByteToWideChar(1251, 0, char_string, -1, NULL, 0);
	res = (LPWSTR) GlobalAlloc(GPTR, ((__int64)res_len + 1) * sizeof(WCHAR));
	MultiByteToWideChar(1251, 0, char_string, -1, res, res_len);
	return res;
}

int64_t getFileSizeWin(const char* file_name) {
	int64_t _file_size = 0;
	HANDLE hFile;
	LPCWSTR file_name_ = CharToLPWSTR(file_name);
	hFile = CreateFileW(file_name_, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		_file_size = -1;
	}
	else {
		LARGE_INTEGER u_winFsz;
		GetFileSizeEx(hFile, &u_winFsz);
		CloseHandle(hFile);
		_file_size = u_winFsz.QuadPart;
	}
	return _file_size;
}

int64_t getFileSize(const char* file_name) {
	if (isWindows(__os__())) return getFileSizeWin(file_name);
	if (isLinux(__os__())) {
		printf("\n[Warning!] Haha, not ready for Linux OS actually, but in theory...\n");
		return -1;
	}
	return -2;
}

//

const char* __os__() {
#ifdef _WIN32
	return "Windows";
#elif _WIN64
	return "Windows 64-bit";
#elif __APPLE__ || __MACH__
	return "Mac OSX";
#elif __linux__
	return "Linux";
#elif __FreeBSD__
	return "FreeBSD";
#elif __unix || __unix__
	return "Unix";
#else
	return "Other";
#endif
}