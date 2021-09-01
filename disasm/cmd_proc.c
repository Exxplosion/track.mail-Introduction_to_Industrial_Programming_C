#include "cmd_proc.h"


void cmd_begin(proc* CPU)
{
	CPU->ax = 0;
	CPU->bx = 0;
	CPU->cx = 0;
	CPU->dx = 0;
	(CPU->stack_proc) = stack_create(100);
}


void cmd_in(proc* CPU)
{
	int a;
	scanf("%d", &a);
	stack_push((CPU->stack_proc), a);
}


void cmd_pop(char text[], proc* CPU, int i)
{
	//printf("asda");
	if(text[i+1] == 50)
	{
		CPU->ax = stack_pop(CPU->stack_proc);
	//	printf("asda popp%d\n", CPU->ax);
		return;
	}

	if(text[i+1] == 51)
	{
		CPU->bx = stack_pop(CPU->stack_proc);
	//	printf("asda %d \n", CPU->ax);
		return;
	}
	if(text[i+1] == 52)
	{
		CPU->cx = stack_pop(CPU->stack_proc);
	//	printf("asda popp%d\n", CPU->ax);
		return;
	}

	if(text[i+1] == 53)
	{
		CPU->dx = stack_pop(CPU->stack_proc);
	//	printf("asda %d \n", CPU->ax);
		return;
	}
}

void cmd_out(proc* CPU)
{
	printf("OUT %d \n", stack_pop(CPU->stack_proc));
}


void cmd_add(proc* CPU)
{
	int a = stack_pop(CPU->stack_proc) + stack_pop(CPU->stack_proc);
	stack_push(CPU->stack_proc, a);
}


void cmd_mul(proc* CPU)
{
	int a = stack_pop(CPU->stack_proc) * stack_pop(CPU->stack_proc);
	stack_push(CPU->stack_proc, a);
}

void cmd_div(proc* CPU)
{
	int div = stack_pop(CPU->stack_proc) / stack_pop(CPU->stack_proc);
	stack_push(CPU->stack_proc, div);
}

void cmd_push(char text[], proc* CPU, int i)
{
	//printf("asda");
	if(text[i+1] == 50)
	{
		stack_push(CPU->stack_proc, CPU->ax);
		//printf("asda\n");
		return;
	}

	if(text[i+1] == 51)
	{
		stack_push(CPU->stack_proc, CPU->bx);
		return;
	}
	if(text[i+1] == 52)
	{
		stack_push(CPU->stack_proc, CPU->cx);
		//printf("asda\n");
		return;
	}

	if(text[i+1] == 53)
	{
		stack_push(CPU->stack_proc, CPU->dx);
		return;
	}
	//printf(" push %d\n", text[i+1]);
	stack_push(CPU->stack_proc, text[i+1]);
	//stack_dump(CPU->stack_proc, 4);
}


void cmd_jmp(char text[], int* i)
{
	*i = text[*i+1] - 2;
	printf("\n jmp on JMP %d \n ", *i);
}

void cmd_je(char text[], int* i, proc* CPU)
{
	Data a = stack_pop(CPU->stack_proc);
	if (stack_get(CPU->stack_proc) == a)
	{
		*i = text[*i+1] - 2;
		printf("\n jmp on JE %d \n ", *i);
	}
	stack_push(CPU->stack_proc, a); 
}

void cmd_jae(char text[], int* i, proc* CPU)
{
	Data a = stack_pop(CPU->stack_proc);
	if (stack_get(CPU->stack_proc) >= a)
	{
		*i = text[*i+1] - 2;
		printf("\n jmp on JaE %d \n ", *i);
	}
	stack_push(CPU->stack_proc, a); 
}

void cmd_end(proc *CPU)
{
	stack_destroy(CPU->stack_proc);
}


void cmd_call(char text[], int* i, proc* CPU, callret *ret_stack)
{
	printf("shya %d\n", *i);
	stack_push(ret_stack->stack_ret, (*i)+2); 
	printf("poloshil %d\n", (*i)+2);
	*i = text[*i+1] - 2;
}

void cmd_ret(int* i, callret *ret_stack)
{
	int top_ret = ret_stack->stack_ret->n;

	if (top_ret)
	{
		*i = stack_pop(ret_stack->stack_ret) - 2;
		printf("vernyl tebya na %d i", *i);
	}
}