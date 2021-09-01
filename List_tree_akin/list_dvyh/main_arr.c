#include "dv_list_array_func.h"


int main()
{

	List_info *list_1 = list_create(20);
	FILE * output = fopen("rez.dot", "w");

	push_head(list_1, 1);
	push_head(list_1, 2);
	push_head(list_1, 3);
	pop_head(list_1);
	insert_before_elem(list_1, 2, 25);
	insert_before_elem(list_1, 2, 25);
	pop_head(list_1);
	insert_before_index(list_1, 1, 30);
	insert_before_index(list_1, 1, 27);
	delet_index(list_1, 4);
	printf("asdasdasd %d\n", number_free_block(list_1));
	//insert_before_index(list_1, 2, 25);

	list_dump(list_1, output);
	print_arr(list_1);
	list_destroy(list_1);
	fclose(output);
	system ("dot -Tpng rez.dot -o list.png");
	system("gio open list.png");

}