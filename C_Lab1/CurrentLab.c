#include "CurrentLab.h"

int sumOfDigits(int n) {
    unsigned int N = llabs((__int64)n);
    int r = 0;
    while (N != 0)
    {
        r += N % 10;
        N /= 10;
    }
    return r;
}

string int32ToBinary(__int32 n)
{
    string mask = convertToBinary(n, "00000000000000000000000000000000");
    if (n < 0) {
        mask = inverseBinary(mask);
        mask = binToComplement(mask);
    }
    return trim(formatBinaryString(mask, ' '));
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

string inverseBinary(string masked_bin) 
{
    int i = 0;
    CharList cList = initCharList(1);
    while (masked_bin[i] != '\0') {
        char tmp = (char)('0' + (masked_bin[i] ^ '1'));
        pushToCharList(&cList, &i, masked_bin[i]);
    }
    return buildString(cList, i);
}

string binToComplement(string masked_bin)
{
    int i = 0;
    CharList sbin = initCharList(1);
    while (masked_bin[i] != '\0') {
        pushToCharList(&sbin, &i, masked_bin[i]);
    }
    for (int j = i; j >= 2; j-=2) {
        sbin[j - 1] = (char)('0' + (sbin[j - 1] ^ '1'));
        if (sbin[j - 1] == '0') {
            sbin[j - 2] = ('0' + (sbin[j - 2] ^ '1'));
            if (sbin[j - 2] == '1') break;
        }
        else break;
    }
    return buildString(sbin, i);
}



string formatBinaryString(string s_bin, char delimiter) {
    int i = 0;
    int j = 0;
    CharList cList = initCharList(1);
    while (s_bin[j] != '\0') {
        if(i % 5 == 0) pushToCharList(&cList, &i, delimiter);
        pushToCharList(&cList, &i, s_bin[j]);
        j++;
    }
    return buildString(cList, i);
}

string convertToBinary(int n, string mask)
{
    int i = 0;
    unsigned int N = llabs((__int64)n);
    CharList cList = initCharList(1);
    while (mask[i] != '\0') {
        pushToCharList(&cList, &i, mask[i]);
    }
    int j = 1;
    while (N != 0)
    {
        char tmp = (char)('0' + (N % 2));
        if (i - j < 0) break;
        cList[i - j] = tmp;
        j++;
        N /= 2;
    }
    return buildString(cList, i);
}



