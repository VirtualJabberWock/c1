#include "DebugUtils.h"
#include "OSystem.h"

static string last_error_channel0;
static string last_error_channel1;
static string last_error_channel2;
static string last_error_channel3;

static string debug_channel0;
static string debug_channel1;
static string debug_channel2;

void panic(string msg) {
	printf_s(msg);
	printf_s("\n\nTerminating process...\n");
	if (isWindows(__os__())) ExitProcess(1);
	else exit(1);
}

void printIntArray(int* array, int len) {
	printf("\n");
	for (int i = 0; i < len; i++) {
		printf_s("%d ", array[i]);
	}
	printf("\n");
}

void setLastError(int channel, string value) {
	if (channel == 0) last_error_channel0 = value;
	if (channel == 1) last_error_channel1 = value;
	if (channel == 2) last_error_channel2 = value;
	if (channel == 3) last_error_channel3 = value;
}

string getLastError(int channel) {
	if (channel == 0) return last_error_channel0;
	if (channel == 1) return last_error_channel1;
	if (channel == 2) return last_error_channel2;
	if (channel == 3) return last_error_channel3;
	return "Unknown channel";
}

void setTemp(int channel, string value) {
	if (channel == 0) debug_channel0 = value;
	if (channel == 1) debug_channel1 = value;
	if (channel == 2) debug_channel2 = value;
}

string getTemp(int channel) {
	if (channel == 0) return debug_channel0;
	if (channel == 1) return debug_channel1;
	if (channel == 2) return debug_channel2;
	return "Unknown channel";
}