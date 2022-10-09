#include "FileUtils.h"

int openFile(FILE** hFile, string filename) {
    return fopen_s(hFile, filename, "r");
}

void openFile_s(FILE** hFile, string filename) {
    setTemp(FILENNAME_CHANNEL, filename);
    handleIOError(fopen_s(hFile, filename, "r"), "OPEN_FILE_ERROR: ");
}

void openFileW_s(FILE** hFile, string filename) {
    handleIOError(fopen_s(hFile, filename, "w"), "OPEN_FILE_ERROR: ");
}

int openFileW(FILE** hFile, string filename) {
    return fopen_s(hFile, filename, "w");
}

void closeFile(FILE* hFile) {
    handleIOError(fclose(hFile), "CLOSING_FILE_ERROR: ");
}

int readAllNumbers(FILE* hFile, int** array, int* readed, string format) {
    int tmp;
    int i = 0;
    if (hFile == 0) return ERROR_CANT_READ;
    while (fscanf_s(hFile, format, &tmp) != EOF) {
        expandIntList(array, i + 1);
        (*array)[i] = tmp;
        i++;
    }
    *readed = i;
    if (i == 0) return ERROR_CANT_READ;
    else return STATUS_SUCCESS;
}

void readAllNumbers_s(FILE* hFile, int** array, int* readed, string format) {
    handleIOError(
        readAllNumbers(hFile, array, readed, format),
        "FILE_SCAN_ERROR: "
    );
}

void readAllLines_s(FILE* hFile, string** bucket, int* readed) {
    int status = STATUS_SUCCESS;
    int i = 0;
    if (hFile == 0) return ERROR_CANT_READ;
    int s = 1;
    while (s > 0) {
        const char buffer[2049] = { 0 };
        s = fscanf_s(hFile, "%s2049", &buffer, 2049);
        if (s == 0) {
            status = ERROR_BUFFER_OVERFLOW;
            break;
        }
        if (s == -1) break;
        expandBucket(bucket, i + 1);
        (*bucket)[i] = str_copy(buffer);
        i++; 
    }
    *readed = i;
    handleIOError(status, "Input file: ");
}

void writeAllLines_s(FILE* hFile, string* lines, int len)
{
    int status = STATUS_SUCCESS;
    int tmp;
    for (int i = 0; i < len; i++) {
        tmp = fprintf_s(hFile, "%s", lines[i]);
        if (tmp == 0) 
        {
             status = ERROR_CANT_WRITE;
             break;
        }
        if (tmp < 0) {
            status = tmp;
            break;
        }
    }
    handleIOError(status, "File writer: ");
}

int writeAllNumbers(FILE* hFile, int* array, int len, string format) {
    int tmp;
    for (int i = 0; i < len; i++) {
        tmp = fprintf_s(hFile, "%d ", array[i]);
        if (tmp == 0) return ERROR_CANT_WRITE;
        if (tmp < 0) return tmp;
    }
    return STATUS_SUCCESS;
}

void writeAllNumbers_s(FILE* hFile, int* array, int len, string format) {
    handleIOError(
        writeAllNumbers(hFile, array, len, format),
        "FILE_WRITE_ERROR: "
    );
}

void handleIOError(int status, string msg) {
    if (status == STATUS_SUCCESS) return;
    printf_s(msg);
    if (status == ERROR_CANT_READ) {
        printf_s("Can't READ data from file");
        status = 0;
    }
    if (status == ERROR_CANT_WRITE) {
        printf_s("Can't WRITE data to file");
        status = 0;
    }
    if (status == ERROR_BUFFER_OVERFLOW) {
        printf_s("Buffer overflow, max decimal number is 10^1024 (also very big number)");
        status = 0;
    }
    if (status == 2) {
        printf_s(str_f("File <%> don`t exists!", getTemp(FILENNAME_CHANNEL)));
        status = 0;
    }
    if (status != 0) {
        printf_s("Unexpected error %d", status);
    }
    panic("\n...");
}

void _handleIOError(int status) {
    handleIOError(status, "IO Error: ");
}
