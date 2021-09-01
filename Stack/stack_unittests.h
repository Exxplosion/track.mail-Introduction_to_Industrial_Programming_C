#ifndef STACK_UNITTESTS_H
#define STACK_UNITTESTS_H
#include "stack_func.h"

#define unittest(what, op, ref, number) \
		if  ((what) op (ref)) \
		{ 		\
			printf("!!!!!!UNIT #%d TEST PASSED!!!!!\n", number); \
		} \
		else \
		{ \
			stack_dump(Stack_1); \
			printf("!!!!UNIT #%d TEST NOT PASSED!!!!!\n", number); \
		} \


void UNIT_1(Stack *s);
//void UNIT_2(Stack *s);
void UNIT_3(Stack *s);
void UNIT_4(Stack *s);
void UNIT_5(Stack *s);


	
#endif