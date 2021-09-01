#include "working_file.h"
#include "stack_func.h"
#include "cmd_proc.h"


#define CMD_DEF(name, code) \
\
	fprintf(fp, "%s ", name);\
	if(text[i+1] == 50) \
	{ \
		fprintf(fp, "%s", "ax"); \
		fprintf(fp, "%s\n", "");\
		break;\
	}\
	if(text[i+1] == 51) \
	{ \
		fprintf(fp,"%s", "bx"); \
		fprintf(fp, "%s\n", "");\
		break;\
	}\
	if(text[i+1] == 52) \
	{ \
		fprintf(fp, "%s", "cx"); \
		fprintf(fp, "%s\n", "");\
		break;\
	}\
	if(text[i+1] == 53) \
	{ \
		fprintf(fp,"%s", "dx"); \
		fprintf(fp, "%s\n", "");\
		break;\
	}\
	fprintf(fp, "%d", text[i+1]); \
	fprintf(fp, "%s\n", "");\

int main()
{
	int count_lines;
	char *text;
	proc CPU;

	CPU.stack_proc = stack_create(1024); 

	callret ret_stack;

	ret_stack.stack_ret = stack_create(1024);

	labels label[100];// {"sss", 101010};

	int size_machine_code;
	if ((text = read_file_in_array(&size_machine_code)) == NULL)
	{	
		perror("can't read file");
	}

	FILE *fp = fopen ("file_d4.txt", "wb");

	int i = 0;
	//printf("%d \n", size_machine_code);
	int count_label2 = 0;

	for (i = 0; i < size_machine_code; i = i+2)
	{
		printf("text[%d]:  %x\n",i, text[i]);
		if (text[i] == -1)
		{
			fprintf(fp, "%d", count_label2++);
			fprintf(fp, "%c", ':');
			fprintf(fp, "%s\n", "");
		}

		switch (text[i])
		{
			case 1:
				printf("do begin\n");
				cmd_begin(&CPU);
				CMD_DEF("begin", 1);
				break;
			case 2:
				printf("do push\n");
				cmd_push(text, &CPU, i);
				CMD_DEF("push", 2);
				break;
			case 3:
				printf("do pop\n");
				cmd_pop(text, &CPU, i);
				CMD_DEF("pop", 2);
				break;
			case 4:
				printf("do out\n");
				cmd_out(&CPU);
				CMD_DEF("out", 2);
				break;
			case 5:
				printf("do ret\n");
				cmd_ret(&i, &ret_stack);
				CMD_DEF("ret",5)
				break;
			case 6:
				printf("do call\n");
				cmd_call(text, &i, &CPU, &ret_stack);
				CMD_DEF("call",6);
				break;
			case 7:
				cmd_add(&CPU);
				printf("do add\n");
				CMD_DEF("add", 2);
				break;
			case 8:
				printf("do div\n");
				cmd_div(&CPU);
				CMD_DEF("div", 2);
				break;
			case 9:
				printf("do mul\n");
				cmd_mul(&CPU);
				CMD_DEF("mul", 2);
				break;
			case 10:
				cmd_jmp(text, &i);
				printf("do jmp\n");
				CMD_DEF("jmp", 2);
				break;
			case 11:
				cmd_je(text, &i, &CPU);
				CMD_DEF("je", 2);
				break;
			case 12:
				printf("do in\n");
				cmd_in(&CPU);
				break;
			case 14:
				printf("do jae\n");
				cmd_jae(text, &i, &CPU);
				CMD_DEF("jae", 2);
				break;
			default:
				break;
		}

	} 
}