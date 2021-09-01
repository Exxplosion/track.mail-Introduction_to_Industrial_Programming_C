#ifndef CMD_PROC_H
#define CMD_PROC_H

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


void cmd_push(char text[], proc* CPU, int i);
void cmd_begin(proc* CPU);
void cmd_in(proc* CPU);
void cmd_pop(char text[], proc* CPU,int i);
void cmd_out(proc* CPU);
void cmd_add(proc* CPU);
void cmd_div(proc* CPU);
void cmd_mul(proc* CPU);
void cmd_jmp(char text[], int* i);
void cmd_je(char text[], int* i, proc* CPU);
void cmd_end(proc *CPU);
void cmd_call(char text[], int* i, proc* CPU, callret *ret_stack);
void cmd_ret(int* i, callret *ret_stack);
void cmd_jae(char text[], int* i, proc* CPU);




#endif