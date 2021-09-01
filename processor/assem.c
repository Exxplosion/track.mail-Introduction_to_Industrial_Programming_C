#include "working_file.h"
#include "stack_func.h"
#include "proc_func.h"

#define CMD_DEF(name, code) \
\
 		if(!strncmp(line[i].lineptr, name, strlen(name)))\
 		{\
			printf("DETECTED %s, ZANES %d\n",name, code);\
			fprintf(fp, "%c", code);\
			fprint_arg(line[i].lineptr+strlen(name), label, fp, count_label);\
 		}\

void fprint_arg(char line[], labels* label, FILE *fp, int count_label)
{
	if(strncmp(line, "ax", strlen("ax")) == 0)
	{
		fprintf(fp, "%c", 50);
		return;
	}

	if(strncmp(line, "bx", strlen("bx")) == 0)
	{
		fprintf(fp, "%c", 51);
		return;
	}

	for (int j = 0; j < count_label; j++)
	{
		printf("%d", j);
		if(strncmp(line, label[j].name, strlen(label[j].name)) == 0)
		{
			printf("eanana %s asdasda %s, %d asdsa %d\n", line, label[j].name, label[j].number_line, j);
			fprintf(fp, "%c", label[j].number_line);
			return;
		}
	}

	printf(" ATOI ETECTED %d \n\n", atoi(line));
	fprintf(fp, "%c", atoi(line));
}



int main()
{
	int count_lines;
	char *text;
	//proc CPU;

	//CPU.stack_proc = stack_create(1024); 

	callret ret_stack;

	ret_stack.stack_ret = stack_create(1024);

	labels label[100] = {"sss", 101010};

	if ((text = read_file_in_array()) == NULL)
	{	
		perror("can't read file");
	}

	lines* line = NULL;

	if ((line = start_of_lines(text, &count_lines)) == NULL)
	{
		perror("nope mem");
	}

	//int n = line[3].len_line;
	//printf("%.*s (%d)\n", n, line[3].lineptr, line[3].len_line);
	//printf("%d", count_lines);
	int count_label = 0;
	int i = 0;

	for(i = 0; i < count_lines; i++)
	{
		my_strcmp_found_labels(line[i], label, i, &count_label); //сразу заменяет найденные метки в исходном коде на числа
		printf("fdfdfdfdfddf i %d %s\n", i, label[0].name);
	}

	FILE *fp = fopen ( "file2.txt", "wb" );
		printf("fdfdfdfdfddf vlad ggg%d %s\n",i,  label[1].name);

	int count_label2 = 0;


//каждая строка - два байта (команда и ее аргументы, в случае метки - первый байт - "байт метки(255)" и байт номера строки)

//то есть процессор видит метку - ему похуй




	for(i = 0; i < count_lines; i++)
	{
		if (line[i].lineptr[1] == ':')
		{
			fprintf(fp, "%c", 255);
			fprintf(fp, "%c", count_label2++); /// номер лигии юзай
		}
		//metki sdleai
		CMD_DEF("begin", 1);
		CMD_DEF("push", 2);
		CMD_DEF("pop", 3);
		CMD_DEF("out", 4);
		CMD_DEF("ret", 5);
		CMD_DEF("call", 6);
		CMD_DEF("add", 8);
		CMD_DEF("div", 9);
		CMD_DEF("mul", 10);
		CMD_DEF("jmp", 11);
		CMD_DEF("je", 12);
		CMD_DEF("end", 13);
	}

	fclose(fp);
	
}