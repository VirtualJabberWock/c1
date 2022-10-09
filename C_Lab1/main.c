#include <stdio.h>
#include "pch.h"

#define BufferSize_s 256
#define BufferReadFormat "%257[^\n\r]"

#define ERR_INPUT_INVALID "[ERR] Invalid input. Max filename length - 100 chars, min - 1 char."

#define ERR_FN_MANY "[ERR] Invalid syntax. Too many arguments"
#define ERR_FN_BAD_OUTPUT "[ERR] Output file name are missed as a second argument"
#define ERR_FN_BAD "[ERR] Invalid syntax. Output & Input file names are missed"

#define ERR_FILE_BIG "[ERR] Input file too big! Max size is 256 MB"
#define ERR_FILE_NOPE "[ERR] Input file has no integers!"
#define ERR_FILE_MANY "[ERR] Input file should has only one integer"
#define ERR_FILE_EMPTY "[ERR] Input file is empty!"
#define ERR_FILE_OPEN "[ERR] I/O: Problem with open file!"

//Todo add "c" files to every ".h"

void handleSyntaxErrors(int args_c);
void handleInputError(string input_str, int atoi_status);
void handleWinIOError(string fn1, string fn2);

static const MAX_FILE_SIZE = 1024 * 1024 * 256;

int main(int argc, const char** argv) {
	//BeforeLoad();

	string input_fn;
	string output_fn;

	if (argc > 1) {
		if (argc > 3) panic(ERR_FN_MANY);
		if (argc == 2) panic(ERR_FN_BAD_OUTPUT);
		input_fn = argv[1];
		output_fn = argv[2];
	}
	else
	{
		printf_s("Enter an input and output filenames:\n> ");
		const char input_buf[BufferSize_s];
		int input_status =
			scanf_s(BufferReadFormat, &input_buf, BufferSize_s);
		if (input_status == 0) panic(ERR_INPUT_INVALID);

		//clear ' ' dublicates, and clear ' ' before and after string
		string raw_input = trim(input_buf);

		int args_c = 0;
		string* args = split(raw_input, ' ', &args_c);
		handleSyntaxErrors(args_c); // ?! panic
	
		input_fn = str_copy(args[0]);
		output_fn = str_copy(args[1]);
	
		freeBucket(args, args_c); // free user input 
	}

	handleWinIOError(input_fn, output_fn);

	if (getFileSize(input_fn) > MAX_FILE_SIZE) panic(ERR_FILE_BIG);
	if (getFileSize(input_fn) == 0) panic(ERR_FILE_EMPTY);

	FILE* f_input;
	openFile_s(&f_input, input_fn);
	if (f_input == NULL) panic(ERR_FILE_OPEN);
	string* file_raw_data = initBucket(1);
	int readed = 0;
	readAllLines_s(f_input, &file_raw_data, &readed);
	if (readed == 0) panic(ERR_FILE_NOPE);
	if (readed > 1) {
		printf("\n[Warning!] Input file have %d lines\n\n", readed);
		panic(ERR_FILE_MANY);
	}
	closeFile(f_input);

	__int32 N = 0;
	int parse_status = parseInteger32(file_raw_data[0], &N);
	handleInputError(file_raw_data[0], parse_status);

	freeBucket(file_raw_data, readed); //free input file data

	printf("%d\n", sumOfDigits(N));
	string binary_sequence = int32ToBinary(N);
	printf("%s\n", binary_sequence);

	FILE* f_output;
	openFileW_s(&f_output, output_fn);
	if (f_output == NULL) panic(ERR_FILE_OPEN);
	string* output_bucket = initBucket(1);
	output_bucket[0] = binary_sequence;
	writeAllLines_s(f_output, output_bucket, 1);
	system("pause");
	return 0;
}



void handleInputError(string input_str, int s)
{
	int len = getStringLength(input_str);
	if (s == 0) return;
	if (s > 0) { // BAD SYMBOL AT SOME POSITION (pos = s)
		if (len < 40) {
			CharList tmp;
			tmp = initCharList(len + 2);
			subCharList(input_str, tmp, 0, s);
			tmp[s] = tmp[s-1];
			tmp[s - 1] = '[';
			tmp[s+1] = '\0';
			printf(tmp);
			printf("]... <-- Not a digit\n");
		}
		else {
			printf("Symbol [%c] at pos %d - not a digit!\n",input_str[s - 1], s-1);
		}
		panic("File has invalid input. Should be a decimal number");
	}

	if (len < 16) {
		panic(
			str_f("Overflow. Can't put number '%' in INT32 (4 bytes) buffer", input_str)
		);
		return;
	}

	CharList tmp;
	tmp = initCharList(20);
	subCharList(input_str, tmp, 0, 16);
	tmp[16] = '.'; tmp[17] = '.';
	tmp[18] = '.'; tmp[19] = '\0';
	panic(
		str_f("Overflow. Can't put (number) '%' in INT32 (4 bytes) buffer", tmp)
	);
	
}

void handleSyntaxErrors(int args_c)
{
	if (args_c == 0) panic(ERR_FN_BAD);
	if (args_c == 1) panic(ERR_FN_BAD_OUTPUT);
	if (args_c > 2) panic(ERR_FN_MANY);
}

void handleWinIOError(string fn1, string fn2) {
	int l1 = getStringLength(fn1);
	int l2 = getStringLength(fn2);
	if (l1 > 100 || l2 > 100) panic(ERR_INPUT_INVALID);
}

