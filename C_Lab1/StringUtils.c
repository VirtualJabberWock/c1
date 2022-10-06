#include "StringUtils.h"
#include "DynamicList.h"

string clearDublicateSpaces(string str)
{
	int i = 0;
	CharList buf = initCharList(1);
	int buf_len = 0;
	char isLastSpace = 0;
	while(str[i] != '\0'){
		if (isLastSpace && str[i] == ' ') {}
		else pushToCharList(&buf, &buf_len, str[i]);
		isLastSpace = (str[i] == ' ');
		i++;
	}
	return buildString(buf, buf_len);
}

int getStringLength(string str)
{
	int i = 0;
	while (str[i] != '\0') i++;
	return i;
}

int parseInteger32(string str, __int32 *out)
{
	int i = 0;
	long long result = 0;
	int tmp;
	int sign = 1;
	if (str[0] == '-') {
		sign = -1;
		i = 1;
	}
	long long intMax = INT_MAX + ((long long)max(0, -1 * sign));
	while (str[i] != '\0') {
		if (str[i] >= '0' || str[i] <= '9') {
			tmp = (str[i] - '0') * (i * 10);
		}
		else return 0;
		if (result + tmp > intMax) return -1;
		result += tmp;
		i++;
	}
	*out = (__int32) (result * sign);
	return 1;
}

string str_c(string str1, string str2) {
	int i = 0;
	CharList buf = initCharList(1);
	int buf_len = 0;
	while (str1[i] != '\0') {
		pushToCharList(&buf, &buf_len, str1[i]); i++;
	}
	while (str2[i] != '\0') {
		pushToCharList(&buf, &buf_len, str2[i]); i++;
	}
	return buildString(buf, buf_len);
}

string str_f(string format, string str2) {
	int i = 0;
	CharList buf = initCharList(0);
	buf[0] = '\0';
	int buf_len = 0;
	while (format[i] != '\0') {
		if (format[i] == '%') {
			int j = 0;
			while (str2[j] != '\0') {
				pushToCharList(&buf, &buf_len, str2[j]);
				j++;
			}
		}
		else {
			pushToCharList(&buf, &buf_len, format[i]);
		}
		i++;
	}
	return buildString(buf, buf_len);
}

string str_copy(string str1) {
	int i = 0;
	CharList buf = initCharList(1);
	int buf_len = 0;
	while (str1[i] != '\0') {
		pushToCharList(&buf, &buf_len, str1[i]); i++;
	}
	return buildString(buf, buf_len);
}


string trim(string str)
{
	string str2 = clearDublicateSpaces(str);
	CharList buf = initCharList(1);
	int buf_s = 0;
	int str_len = getStringLength(str2);
	int start = 0, end = str_len;
	if (str[0] == ' ') start++;
	if (str[str_len-1] == ' ') end--;
	for (int i = start; i < end; i++) pushToCharList(&buf, &buf_s, str2[i]);
	return buildString(buf, buf_s);
}

string* split(string str, char delimiter, int* count) {
	string* a = (string*) initBucket(1);
	int bucket_s = 0;
	int i = 0;
	int start = 0, end = 0;
	CharList tmp = initCharList(1);
	tmp[0] = '\0';
	while (str[i] != '\0') {
		if (str[i] == delimiter) {
			tmp = initCharList(end-start+1);
			subCharList(str, tmp, start, end-1);
			pushToBucket(&a, &bucket_s, buildString(tmp, end-start));
			start = i+1;
			end = i;
		}
		end++;
		i++;
	}
	tmp = initCharList(end - start + 1);
	subCharList(str, tmp, start, end);
	pushToBucket(&a, &bucket_s, tmp);
	*count = bucket_s; // [out]
	return a;
}
