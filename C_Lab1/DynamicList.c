#include "DynamicList.h"

//numbers

int* initIntList(int size) {
	return (int*)calloc(size, sizeof(int));
}

void expandIntList(int** list, int new_size) {
	int* tmp = (int*)realloc((void*)(*list), new_size * sizeof(int));
	if (tmp == NULL) panic("List::Memory allocation error!");
	else *list = tmp;
}

void copyIntArray(int* from, int* to, int begin, int end) {
	for (int i = 0; i < (end - begin) + 1; i++) {
		to[i] = from[i + begin];
	}
}

void fillIntList(int* list, int len, int value) {
	for (int i = 0; i < len; i++) {
		list[i] = value;
	}
}

//strings

char* initCharList(int size) {
	char* ptr = malloc(size);
	if (ptr == NULL)
		panic("Out of memory");
	else
		return ptr;
}

void pushToCharList(char** list, int* size, char chr) {
	expandCharList(list, (*size) + 1);
	(*list)[(*size)] = chr;
	*size = *size + 1;
}

const char* buildString(char* string_list, int buffer_size) {
	char* buf0 = initCharList(buffer_size + 1);
	for (int i = 0; i < buffer_size; i++) buf0[i] = string_list[i];
	buf0[buffer_size] = '\0';
	if(string_list != 0) free(string_list); // Dispose
	string_list = 0;
	return buf0;
}

void expandCharList(char** list, int new_size){
	void* address = (*list);
	if (address == NULL) panic("List::Memory allocation error!");
	char* tmp = (char*)realloc((void*)(*list), new_size);
	if (tmp == NULL) panic("CharList::Memory allocation error!");
	else {
		list[0] = tmp;
	}
}

void subCharList(char* from, char* to, int begin, int end)
{
	for (int i = 0; i < (end - begin) + 1; i++) {
		to[i] = from[i + begin];
	}
}

// bucket

obj_ptr* initBucket(int size) {
	return (void*)calloc(size, sizeof(void*));
}

void expandBucket(obj_ptr** bucket, int new_size) {
	void* address = (*bucket);
	if (address == NULL) panic("List::Memory allocation error!");
	char* tmp = (char*)realloc((void*)(bucket[0]), sizeof(void*)*new_size);
	if (tmp == NULL) panic("CharList::Memory allocation error!");
	else {
		bucket[0] = tmp;
	}
}

void pushToBucket(obj_ptr** bucket, int* bucket_size, obj_ptr obj) {
	expandBucket(bucket, (*bucket_size) + 1);
	(*bucket)[(*bucket_size)] = obj;
	*bucket_size = *bucket_size + 1;
}

void freeBucket(obj_ptr* bucket, int bucket_size) {
	for (int i = 0; i < bucket_size; i++) {
		free(bucket[i]);
	}
	free(bucket);
}

