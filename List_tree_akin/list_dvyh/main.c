#include "dv_list_func.h"


int main()
{

	List_info *list_1 = list_create();
	FILE * output = fopen("rez.dot", "w");

	list_push_head(list_1, 1);
	list_push_head(list_1, 2);
	list_push_tail(list_1, 3);
	list_push_tail(list_1, 4);

	insert_after_elem(list_1, 23, 1);
	insert_before_elem(list_1, 23, 1);

	list_dump(list_1, output);

	fclose(output);
	list_destroy(list_1);
	system ("dot -Tpng rez.dot -o list.png");
	system("gio open list.png");

}