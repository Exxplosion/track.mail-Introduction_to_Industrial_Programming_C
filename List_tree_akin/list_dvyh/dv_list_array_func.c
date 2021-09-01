#include "dv_list_array_func.h"

List_info* list_create(int size)
{
	List_info *out = NULL;

	memory_get(out, List_info, 1)
	memory_get(out->next_arr, int, size)
	memory_get(out->prev_arr, int, size)
	memory_get(out->Data_arr, Node, size)

	poison_entry(out, size);

	out->head = -1;
	out->tail = -1;
	out->size_data_arr = 0; //"нет" элементов
	out->size_list = size;
	return out;
}

void poison_entry(List_info *out, int size)
{
	for (int i = 0; i < size; i++)
	{
		out->next_arr[i] = POISON;
		out->prev_arr[i] = POISON;
		out->Data_arr[i].val = POISON;
	}
}

int number_free_block(List_info *list)
{
	for (int i = 0; i <= list->size_list; i++)
	{
		if (list->Data_arr[i].val == POISON)
		{
			list->size_data_arr = list->size_data_arr + 1;
			return i;
		}
	}
	errno = LIST_UNDERFLOW;
	err("LIST_UNDERFLOW");
	return -1;
}

void push_head(List_info *list, Data_node value)
{
	check_size_push

	int numb_ins = number_free_block(list);
	assert(numb_ins != -1);

	list->Data_arr[numb_ins].val = value;

	if (list->head == -1) //first
	{
		list->head = numb_ins; // = 0
		list->tail = numb_ins; // = 0
	}
	else
	{
		list->next_arr[numb_ins] = list->head;
		list->prev_arr[list->head] = numb_ins;
		list->head = numb_ins;
	}
}

void push_tail(List_info *list, Data_node value)
{
	check_size_push

	int numb_ins = number_free_block(list);
	assert(numb_ins != -1);

	list->Data_arr[numb_ins].val = value;

	if (list->tail == -1) //first
	{
		list->head = numb_ins; // = 0
		list->tail = numb_ins; // = 0
	}
	else
	{
		list->prev_arr[numb_ins] = list->tail;
		list->next_arr[numb_ins] = numb_ins;
		list->tail = numb_ins;
	}
}

Data_node pop_head(List_info *list)
{
	check_size_pop

	if (list->head == list->tail) //one elem
	{
		Data_node supp = list->Data_arr[list->head].val;
		list->Data_arr[list->head].val = POISON;
		list->size_data_arr = list->size_data_arr - 1;
		list->head = -1;
		list->tail = -1;
		return supp;
	}
	Data_node supp = list->Data_arr[list->head].val;
	list->Data_arr[list->head].val = POISON;

	int supp_index = list->next_arr[list->head];
	list->next_arr[list->head] = POISON;
	list->head = supp_index;
	list->prev_arr[supp_index] = -1;
	list->size_data_arr = list->size_data_arr - 1;
	return supp;
}

int found_elem(List_info *list, Data_node value)
{
	check_size_pop

	int cur = list->head;

	while (cur != -1)
	{
		if (list->Data_arr[cur].val == value)
			return cur;
		cur = list->next_arr[cur];
	}
	return -1;
}

void insert_after_elem(List_info *list, Data_node value, Data_node ins)
{
	check_size_push

	int index = found_elem(list, value);
	if (index == -1)
		return;
	if (index == list->tail)
	{
		push_tail(list, ins);
		return;
	}

	int numb_ins = number_free_block(list);

	list->Data_arr[numb_ins].val = ins;

	int supp = list->next_arr[index];
	list->next_arr[index] = numb_ins;
	list->next_arr[numb_ins] = supp;

	int index_front = supp;

	supp = list->prev_arr[index_front];
	list->prev_arr[index_front] = numb_ins;
	list->prev_arr[numb_ins] = supp;
}

void delet_elem(List_info *list, Data_node value)
{
	check_size_pop

	int index = found_elem(list, value);
	if (index == -1)
		return;
	if (index == list->tail)
	{
		pop_tail(list);
		return;
	}
	if (index == list->head)
	{
		pop_head(list);
		return;
	}

	list->Data_arr[index].val = POISON;


	int supp = list->next_arr[index];

	list->next_arr[index] = POISON;
	int index_prev = list->prev_arr[index];
	list->next_arr[index_prev] = supp;

	//int supp_2= list->prev_arr[index];
	list->prev_arr[index] = POISON;

	int index_front = supp;
	list->prev_arr[supp] = index_prev;

	list->size_data_arr = list->size_data_arr - 1;
}

void insert_before_elem(List_info *list, Data_node value, Data_node ins)
{
	check_size_push

	int index = found_elem(list, value);
	if (index == -1)
		return;
	if (index == list->head)
	{
		push_head(list, ins);
		return;
	}
	int numb_ins = number_free_block(list);

	list->Data_arr[numb_ins].val = ins;

	int supp = list->prev_arr[index];
	list->prev_arr[index] = numb_ins;
	list->prev_arr[numb_ins] = supp;

	int index_front = supp;

	supp = list->next_arr[index_front];
	list->next_arr[index_front] = numb_ins;
	list->next_arr[numb_ins] = supp;
}

void insert_after_index(List_info *list, int index, Data_node ins)
{
	check_size_push
	check_index

	//int index = found_elem(list, value);
	if (index == -1)
		return;
	if (index == list->tail)
	{
		push_tail(list, ins);
		return;
	}

	int numb_ins = number_free_block(list);
	list->Data_arr[numb_ins].val = ins;

	int supp = list->next_arr[index];
	list->next_arr[index] = numb_ins;
	list->next_arr[numb_ins] = supp;

	int index_front = supp;

	supp = list->prev_arr[index_front];
	list->prev_arr[index_front] = numb_ins;
	list->prev_arr[numb_ins] = supp;
}

void delet_index(List_info *list, int index)
{
	check_size_pop
	check_index

	//int index = found_elem(list, value);
	if (index == -1)
		return;
	if (index == list->tail)
	{
		pop_tail(list);
		return;
	}
	if (index == list->head)
	{
		pop_head(list);
		return;
	}

	list->Data_arr[index].val = POISON;


	int supp = list->next_arr[index];

	list->next_arr[index] = POISON;
	int index_prev = list->prev_arr[index];
	list->next_arr[index_prev] = supp;

	//int supp_2= list->prev_arr[index];
	list->prev_arr[index] = POISON;

	int index_front = supp;
	list->prev_arr[supp] = index_prev;

	list->size_data_arr = list->size_data_arr - 1;
}

void insert_before_index(List_info *list, int index, Data_node ins)
{
	check_size_push
	check_index

	//int index = found_elem(list, value);
	if (index == -1)
		return;
	if (index == list->head)
	{
		push_head(list, ins);
		return;
	}

	int numb_ins = number_free_block(list);

	list->Data_arr[numb_ins].val = ins;

	int supp = list->prev_arr[index];
	list->prev_arr[index] = numb_ins;
	list->prev_arr[numb_ins] = supp;

	int index_front = supp;

	supp = list->next_arr[index_front];
	list->next_arr[index_front] = numb_ins;
	list->next_arr[numb_ins] = supp;
}


Data_node pop_tail(List_info *list)
{
	check_size_pop

	if (list->head == list->tail) //one elem
	{
		Data_node supp = list->Data_arr[list->head].val;
		list->Data_arr[list->head].val = POISON;
		list->size_data_arr = list->size_data_arr - 1;
		list->head = -1;
		list->tail = -1;
		return supp;
	}
	Data_node supp = list->Data_arr[list->tail].val;
	list->Data_arr[list->tail].val = POISON;

	int supp_index = list->prev_arr[list->tail];
	list->prev_arr[list->tail] = POISON;
	list->tail = supp_index;
	list->next_arr[supp_index] = -1;
	list->size_data_arr = list->size_data_arr - 1;
	return supp;
}

void list_dump(List_info *list,FILE* output)
{
	check_size_pop

	fprintf(output, "digraph G{\n");
	fprintf(output, "\t");

	int cur = list->head;

	int i = 0;
	while (cur != -1)
	{
		fprintf(output, "\"%d\" [shape=\"record\", label=\" Next id: %d| Current elem: %d| Number elem: %d| Data: %d | Prev: %d\"];\n", i, list->next_arr[cur], i, cur, list->Data_arr[cur].val, list->prev_arr[cur]);
		cur = list->next_arr[cur];
		i++;
	}
	fprintf(output, "\"NULL_head\" -> \n");

	for (int j = 0; j < i; j++)
	{
			fprintf(output, "%d ->", j);
	}
	fprintf(output, "NULL_tail;\n");
	fprintf(output, "}");
}

void print_arr(List_info *list)
{
	printf("i: ");

	for(int i = 0; i < list->size_list; i++)
	{
		printf(" %d ", i);
	}

	printf("\n");
	printf("Data :");

	for(int i = 0; i < list->size_list; i++)
	{
		printf(" %d ", list->Data_arr[i].val);
	}

	printf("\n");
	printf("Next :");

	for(int i = 0; i < list->size_list; i++)
	{
		printf(" %d ", list->next_arr[i]);
	}

	printf("\n");
	printf("Prev :");

	for(int i = 0; i < list->size_list; i++)
	{
		printf(" %d ", list->prev_arr[i]);
	}

	printf("\n HEAD: %d TAIL: %d \n", list->head, list->tail);
}


void list_destroy(List_info *list)
{
	assert(list != NULL);

	free(list->next_arr);
	list->next_arr = NULL;
	free(list->prev_arr);
	list->prev_arr = NULL;
	free(list->Data_arr);
	list->Data_arr = NULL;
	free(list);
}