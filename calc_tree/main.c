#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "working_file.h"


char *s = NULL;

int main()
{
	char* string = read_file_in_array();
	printf("Answer: %lg\n", getG(string));
	return 0;
}