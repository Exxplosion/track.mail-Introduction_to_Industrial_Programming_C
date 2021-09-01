#include "proc_func.h"


void my_strcmp(char line[], proc* CPU, int* i, labels* label, callret *ret_stack)
{

/*#CMD_DEF(num, name, code) 
 		if(!strcmp(line, name)){
			fprintf(fp, "%c", num);
 		}


 		#include "commands.h" //метка в число 

 		#undef CMD_DEF
*/

	if(strncmp(line, "begin", strlen("begin")) == 0)
		cmd_begin(CPU);

	if(strncmp(line, "in", strlen("in")) == 0) 
		cmd_in(CPU);

	if(strncmp(line, "pop", strlen("pop")) == 0)
		cmd_pop((line + sizeof("pop")), CPU);

	if(strncmp(line, "push", strlen("push")) == 0)
	{
		cmd_push((line + sizeof("push")), CPU);
//				printf("ya titi");
	}

	if(strncmp(line, "out", strlen("out")) == 0)
		cmd_out(CPU);

	if(strncmp(line, "add", strlen("add")) == 0)
		cmd_add(CPU);

	if(strncmp(line, "mul", strlen("mul")) == 0)
		cmd_mul(CPU);

	if(strncmp(line, "div", strlen("div")) == 0)
		cmd_div(CPU);

	if(strncmp(line, "jmp", strlen("jmp")) == 0)
	{
		//printf("ya tffiti");
		cmd_jmp((line + sizeof("jmp")), i, label);
	}

	if(strncmp(line, "je", strlen("je")) == 0)
	{
		cmd_je((line + sizeof("je")), i, label, CPU);
//		printf("ya titi");
	}

	if(strncmp(line, "call", strlen("call")) == 0)
	{
		cmd_call((line + sizeof("call")), i, label, CPU, ret_stack);
//		printf("ya titi");
	}

	if(strncmp(line, "ret", strlen("ret")) == 0)
	{
		cmd_ret(i, ret_stack);
//		printf("ya titi");
	}
	//return;
}



void my_strcmp_found_labels(lines line, labels* label, int i, int* count_label)
{
	//printf("gaga %d %d \n", i, *count_label);
	if (line.lineptr[line.len_line-1] == ':')
	{
		label[*(count_label)].number_line = i;
		strncpy(label[*(count_label)].name, line.lineptr, 10);
		//supp_line[line.len_line-1] = '\0';
		label[*(count_label)].name[line.len_line-1] = '\0';
		printf("label %s nomer %hu %d\n", label[*(count_label)].name, label[*(count_label)].number_line, *count_label);
		//printf("%s\n", line.lineptr);
		*(count_label) = *(count_label) + 1;
	}
}



void cmd_push(char line[], proc* CPU)
{
	//printf("asda");
	if(strncmp(line, "ax", strlen("ax")) == 0)
	{
		stack_push(CPU->stack_proc, CPU->ax);
		//printf("asda\n");
		return;
	}
	if(strncmp(line, "bx", strlen("bx")) == 0)
		stack_push(CPU->stack_proc, CPU->bx);

	stack_push(CPU->stack_proc, atoi(line));
}


void cmd_begin(proc* CPU)
{
	CPU->ax = 0;
	CPU->bx = 0;
	CPU->cx = 0;
	CPU->dx = 0;
	(CPU->stack_proc) = stack_create(10);
	//printf("ok\n");
}

void cmd_in(proc* CPU)
{
	int a;
	scanf("%d", &a);
	stack_push((CPU->stack_proc), a);
}

void cmd_pop(char line[], proc* CPU)
{
	//printf("asda");
	if(strncmp(line, "ax", strlen("ax")) == 0)
	{
		CPU->ax = stack_pop(CPU->stack_proc);
		//printf("asda popp%d\n", CPU->ax);
		return;
	}

	if(strncmp(line, "bx", strlen("bx")) == 0)
	{
		CPU->bx = stack_pop(CPU->stack_proc);
		//printf("asda\n");
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

void cmd_jmp(char line[], int* i, labels* label)
{
	//printf("JMP %s\n", line);
	for (int j = 0; j < 100; j++)
	{
		//printf("JMP %s %s\n", line, label[j].name);
		if(strncmp(line, label[j].name, strlen(label[j].name)) == 0)
		{
			//printf("ahahahah");
			*i = label[j].number_line;
			return;
		}
	}
}

void cmd_je(char line[], int* i, labels* label, proc* CPU)
{
	for (int j = 0; j < 100; j++)
	{

		if(strncmp(line, label[j].name, strlen(label[j].name)) == 0)
		{
			Data a = stack_pop(CPU->stack_proc);
		//printf("JEEE %d %d %s\n", stack_get(CPU->stack_proc), a, line);

			if (stack_get(CPU->stack_proc) == a)
				{
					*i = label[j].number_line;
				}

			stack_push(CPU->stack_proc, a); 
			return;
		}
	}
}

void cmd_call(char line[], int* i, labels* label, proc* CPU, callret *ret_stack)
{
	printf("shya %d\n", *i);
	for (int j = 0; j < 100; j++)
	{

		if(strncmp(line, label[j].name, strlen(label[j].name)) == 0)
		{
			stack_push(ret_stack->stack_ret, (*i)+1); 
			printf("poloshil %d\n", (*i)+1);
			*i = label[j].number_line;
			return;
		}
	}
}

void cmd_ret(int* i, callret *ret_stack)
{
	int top_ret = ret_stack->stack_ret->n;

	if (top_ret)
	{
		*i = stack_pop(ret_stack->stack_ret);
		printf("vernyl tebya na %d i", *i);
	}
}