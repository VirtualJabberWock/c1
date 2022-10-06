#pragma once
#include "pch.h"
void BeforeLoad() {
	printf("-=-=-=-=-=-= TEST =-=-=-=-=-=\n\n");
	FILE* tmp;
	openFileW_s(&tmp, "input.txt");
	int* t_out = initIntList(1);
	t_out[0] = 17;
	writeAllNumbers(tmp, t_out, 1, "%d");
	closeFile(tmp);
	system("start input.txt");
	panic("=-=-=-=-= END OF TEST =-=-=-=-\n");
}
