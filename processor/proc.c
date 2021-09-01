#include "working_file.h"
#include "stack_func.h"
#include "proc_func.h"



int main()
{
	int count_lines;
	char *text;
	proc CPU;

	CPU.stack_proc = stack_create(1024); 

	callret ret_stack;

	ret_stack.stack_ret = stack_create(1024);

	labels label[100]; //{"shs", 121212};
			printf("fdfdfdfdfddf i 	 %s\n",label[0].name);

	if ((text = read_file_in_array()) == NULL)
	{
		perror("can't read file");
	}

	lines* line = NULL;

	if ((line = start_of_lines(text, &count_lines)) == NULL)
	{
		perror("nope mem");
	}

	int count_label = 0;
	int i = 0;

	for(i = 0; i < count_lines; i++)
	{
		my_strcmp_found_labels(line[i], label, i, &count_label);
	}


	for(i = 0; i < count_lines; i++)
	{
		printf("  %d   %s   \n", i, line[i].lineptr);
		my_strcmp(line[i].lineptr, &CPU, &i, label, &ret_stack);
	}

}