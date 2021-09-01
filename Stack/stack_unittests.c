#include "stack_unittests.h"
#include "stack_func.h"
#include <stdio.h>


void UNIT_1(Stack *s)
{
	stack_pop(s);

	if (errno == STACK_UNDERFLOW)
	{
		printf("!!UNIT #1 TEST PASSED!!\n");
		//stack_dump(s, 0);
	}
}

/*
void UNIT_2(Stack *s)
{
	for (;;)
	{
		stack_push(s, 299); //полностью флудим стек... //не работает(?)

		if (errno == STACK_OVERFLOW)
		{
			printf("!!UNIT #2 TEST PASSED!!\n");
			exit(0);
		}
	}
} */

void UNIT_3(Stack *s)
{
	stack_push(s, 299);
	stack_push(s, 299);
	stack_push(s, 299);
	stack_push(s, 299); //s->a[3]
	s->a[3] = 443; //затёр данные
	stack_OK(s);

	if (errno == STACK_BROKE)
	{
		printf("!!UNIT #3 TEST PASSED!!\n");
	}
}

void UNIT_4(Stack *s)
{
	stack_push(s, 299);

	s->canary_1 = 0xBABA0000;

	stack_OK(s);

	if (errno == STACK_BROKE)
		{

			printf("!!UNIT #4 TEST PASSED!!\n");
		}
}

void UNIT_5(Stack *s) //занесем числа 1-100 и достанем их
{
	enum boolean { NO, YES };
	int flag = YES;
	for(int i = 1; i <= 100; i++)
	{
		stack_push(s, i);
	}

	for(int i = 100; i >= 100; i--)
	{
		if(stack_pop(s) != i)
		{
			flag = NO;
		}
	}
	if (flag) printf("!!UNIT #5 TEST PASSED!!\n");
}