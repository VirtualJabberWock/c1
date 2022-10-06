#pragma once
#include <stdlib.h>
#include "DebugUtils.h"

#define obj_ptr void*

int* initIntList(int size);
void expandIntList(int** array, int new_size);
void fillIntList(int* array, int len, int value);
void copyIntArray(int* from, int* to, int begin, int end);

//

char* initCharList(int size);

void expandCharList(char** list, int new_size);

void subCharList(char* from, char* to, int begin, int end);

/* Push char to dynamic string buffer*/
void pushToCharList(char** list, int* list_size, char chr);

/* Builds const string from dynamic char array & Dispose resources (free memory) */
const char* buildString(char* list, int list_size);

//

obj_ptr* initBucket(int size);
void expandBucket(obj_ptr** bucket, int new_size);
void pushToBucket(obj_ptr** bucket, int* bucket_size, obj_ptr obj);
void freeBucket(obj_ptr* bucket, int bucket_size);
