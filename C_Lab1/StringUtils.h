#pragma once
#define string const char*
#define CharList char*

string clearDublicateSpaces(string str);
int getStringLength(string str);
int parseInteger32(string str, __int32* out);

string trim(string str);
string* split(string, char delimiter, int* parts_count);

string str_copy(string str1);

string str_c(string str1, string str2);

/* replace every '%' to str2 in format string */
string str_f(string format, string str2);

//a
