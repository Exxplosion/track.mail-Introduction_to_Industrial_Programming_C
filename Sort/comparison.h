#ifndef COMPARISON_H
#define COMPARISON_H

//#include <assert.h>


typedef struct
{
	char *lineptr; //массив указателей на начало
	int len_line; 
} lines;


int mystrcmp(const lines *a, const lines *b);
int mystrcmp_last(const lines *a, const lines *b);


#endif