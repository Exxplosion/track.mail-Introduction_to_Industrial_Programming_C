#include "odn_list_func.h"


int main()
{
	Node *root_ptr = (Node*)malloc(sizeof(Node));
	root_ptr= list_create(2);
	FILE * output = fopen("rez.dot", "w");
	list_dump(root_ptr, output);
	list_push(root_ptr, 1);
	list_push(root_ptr, 1);
	//printf(*root):
	list_push(root_ptr, 2);
	delete_last(root_ptr); 
	printf("FFFF %p\n", found_elem(root_ptr, 2));
	fprintf(output, "<graph>\ndigraph G{\n");
	list_dump(root_ptr, output);
	fprintf(output, "}\n</graph>");
	fclose(output);
	return 0;
}