#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "DynamicList.h"
#include "StringUtils.h"

#define string const char*

#define ERROR_CANT_READ        0x133700
#define ERROR_CANT_WRITE       0x133701
#define ERROR_BUFFER_OVERFLOW  0x133702
#define ERROR_EMPTY_FILE  0x133703
#define STATUS_SUCCESS         0x0

#define FILENNAME_CHANNEL 1

#define DYNAMIC_SIZE -1

int openFile(FILE** hFile, string filename);
void openFile_s(FILE** hFile, string filename);

void openFileW_s(FILE** hFile, string filename);
int openFileW(FILE** hFile, string filename);

void closeFile(FILE* hFile);

int readAllNumbers(FILE* hFile, int** array, int* readed, string format);
void readAllNumbers_s(FILE* hFile, int** array, int* readed, string format);


void readAllLines_s(FILE* hFile, string** bucket, int* readed);
void writeAllLines_s(FILE* hFile, string* lines, int len);

int writeAllNumbers(FILE* hFile, int* array, int len, string format);
void writeAllNumbers_s(FILE* hFile, int* array, int len, string format);

void handleIOError(int status, string msg);
void _handleIOError(int status);