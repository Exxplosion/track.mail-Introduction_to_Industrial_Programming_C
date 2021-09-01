#ifndef STACK_FUNC_H
#define STACK_FUNC_H


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

#define SIZE_INCREMENT 256
#define canary_first  0xDED00BAD
#define canary_last  0xBABABEDA
#define POISON 666
#define err(msg) fprintf(stderr, "in FILE %s; line %d; error %d: %s\n", __FILE__, __LINE__, errno, msg);

extern enum
{
	Success,
	ZERO_SIZE, //0
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	STACK_BROKE, //3
	NOPE_MEM
} ERROR_CODE;


typedef int Data;

typedef struct  
{
	unsigned int canary_1;// = 0x0DED0BAD;
	long int hash;
    int n; //top_stack
    int size;
    Data *a;
	unsigned int canary_2; //0xBABABEDA;
} Stack;



Stack* stack_create(int size);
void poison_entry(Stack *s);
void stack_push(Stack *s, Data x);
Data stack_pop(Stack* s);
Data stack_get(Stack* s);
void stack_dump(Stack* s, int hash_2);
void stack_destroy(Stack* s);
int stack_ASSERT(Stack *s);

#endif