#include <stdio.h>
#include "pch.h"

#define BufferSize_s 256
#define BufferReadFormat "%257[^\n\r]"

#define ERR_INPUT_INVALID "Invalid input. Max filename length - 100 chars, min - 1 char."

#define ERR_FN_MANY "Invalid syntax. Too many arguments"
#define ERR_FN_BAD_OUTPUT "Invalid syntax. Output file name are missed as a second argument"
#define ERR_FN_BAD "Invalid syntax. Output & Input file names are missed"

#define ERR_FILE_BIG "Input file too big! Max size is 256 MB"
#define ERR_FILE_NOPE "Input file has no integers!"
#define ERR_FILE_MANY "Input file should has only one integer"
#define ERR_FILE_EMPTY "Input file is empty!"

//Todo add "c" files to every ".h"

void handleSyntaxErrors(int args_c);

static const MAX_FILE_SIZE = 1024 * 1024 * 256;

int main() {
	//BeforeLoad();
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
	
	string input_fn = str_copy(args[0]);  
	string output_fn = str_copy(args[1]);

	freeBucket(args, args_c); // freeBucket

	if (getFileSize(input_fn) > MAX_FILE_SIZE) panic(ERR_FILE_BIG);
	if (getFileSize(input_fn) == 0) panic(ERR_FILE_EMPTY);

	FILE* f_input;
	openFile_s(&f_input, input_fn);
	string* file_raw_data = initBucket(1);
	int readed = 0;
	readAllLines_s(f_input, &file_raw_data, &readed);
	if (readed == 0) panic(ERR_FILE_NOPE);
	printf("%d\n", readed);
	for(int i = 0;i<readed;i++) printf("%s\n", file_raw_data[0]);
	closeFile(f_input);

	__int32 N = 0;
	int s = parseInteger32(file_raw_data[0], &N);
	if (s == 0) panic("File has invalid input. Should be a decimal number");
	if (s == -1) panic(
		str_f(
			"Integer overflow. Can't put number '%' in INT32 (4 bytes) buffer",
			file_raw_data[0]
		)
	);

	printf("\n\n%d", N);

}

/* may call panic! */
void handleSyntaxErrors(int args_c)
{
	if (args_c == 0) panic(ERR_FN_BAD);
	if (args_c == 1) panic(ERR_FN_BAD_OUTPUT);
	if (args_c > 2) panic(ERR_FN_MANY);
}
