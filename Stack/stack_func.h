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


typedef int Data_t;

typedef struct  
{
	unsigned int canary_1;// = 0x0DED0BAD;
	long int hash;
    int n; //top_stack
    int size;
    Data_t *a;
	unsigned int canary_2; //0xBABABEDA;
} Stack;



Stack* stack_create(int size);
void poison_entry(Stack *s);
void stack_push(Stack *s, Data_t x);
Data_t stack_pop(Stack* s);
void stack_dump(Stack* s);
void stack_destroy(Stack* s);
int stack_OK(Stack *s);
int hash_2_get(Stack *s);
int size_stack_get(Stack*s);
void make_hash_pop(Stack *s);
void make_hash(Stack *s, Data_t x);



#endif