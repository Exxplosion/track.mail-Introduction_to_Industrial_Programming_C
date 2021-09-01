#ifndef PROC_FUNC_H
#define PROC_FUNC_H

#include "stack_func.h"
#include "working_file.h"
#include <string.h>
#include <stdio.h>

typedef struct
{
	int ax;
	int bx;
	int cx;
	int dx;	
	Stack *stack_proc;
} proc;

typedef struct
{
	Stack *stack_ret;
} callret;


typedef struct
{
	char name[10];
	unsigned int number_line;
} labels;


void my_strcmp_found_labels(lines line, labels* label, int i, int* count_label);
void my_strcmp(char line[], proc* CPU, int* i,  labels* label, callret *ret_stack);
void cmd_push(char line[], proc* CPU);
void cmd_begin(proc* CPU);
void cmd_in(proc* CPU);
//void cmd_push(proc* CPU);
void cmd_pop(char line[], proc* CPU);
void cmd_out(proc* CPU);
void cmd_add(proc* CPU);
void cmd_div(proc* CPU);
void cmd_mul(proc* CPU);
void cmd_jmp(char line[], int* i, labels* label);
void cmd_je(char line[], int* i, labels* label, proc* CPU);
void cmd_call(char line[], int* i, labels* label, proc* CPU, callret *ret_stack);
void cmd_ret(int* i, callret *ret_stack);




#endif