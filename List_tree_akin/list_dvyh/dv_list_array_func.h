#ifndef DV_LIST_ARRAY_FUNC_H
#define DV_LIST_ARRAY_FUNC_H
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#define err(msg) fprintf(stderr, "in FILE %s; line %d; error %d: %s\n", __FILE__, __LINE__, errno, msg);

#define memory_get(ptr, type, size)																		\
			if ((ptr = (type *) calloc(size, sizeof(type))) == NULL)									\
			{																							\
				errno = NOPE_MEM;																		\
				err("NOPE_MEM");																		\
			}																							\

#define check_size_push																					\
			if (list->size_list <= list->size_data_arr)													\
			{																							\
				errno = LIST_OVERFLOW;																	\
				err("LIST_OVERFLOW");																	\
			}																							\

#define check_size_pop																					\
			if (list->size_data_arr <= 0)																\
			{																							\
				errno = LIST_UNDERFLOW;																	\
				err("LIST_UNDERFLOW");																	\
			}																							\

#define check_index																						\
			if (0 <= index && index <= list->size_data_arr)												\
			{																							\
				int flag = 0;																			\
				int cur = list->head;																	\
				while(cur != -1)																		\
				{																						\
					if (cur == index)																	\
						flag = 1;																		\
					cur = list->next_arr[cur];															\
																										\
				}																						\
				if(flag == 0)																			\
				{																						\
					errno = INVALID_INDEX;																\
					err("INVALID_INDEX");																\
					return;																				\
				}																						\
																										\
			}																							\
			else 																						\
			{																							\
				errno = INVALID_INDEX;																	\
				err("INVALID_INDEX");																	\
				return;																					\
			}																							\


#define POISON -1

enum ERROR_CODE
{
	Success,
	ZERO_SIZE, //0
	LIST_UNDERFLOW,
	LIST_BROKE,
	LIST_OVERFLOW, //3
	NOPE_MEM,
	INVALID_INDEX
};



typedef int Data_node;

typedef struct Node_t Node;

struct Node_t
{
	Data_node val;
};

typedef struct List List_info;

struct List
{
	unsigned int size_list;
	unsigned int size_data_arr;
	int head;
	int tail;
	int *next_arr;
	int *prev_arr;
	Node* Data_arr;
};


List_info* list_create(int size);
void push_head(List_info *list, Data_node value);
void list_dump(List_info *list,FILE* output);
void poison_entry(List_info *out, int size);
void push_tail(List_info *list, Data_node value);
int found_elem(List_info *list, Data_node value);
void insert_after_elem(List_info *list, Data_node value, Data_node ins);
void insert_before_elem(List_info *list, Data_node value, Data_node ins);
Data_node pop_head(List_info *list);
Data_node pop_tail(List_info *list);
void delet_elem(List_info *list, Data_node value);
void list_destroy(List_info *list);
void insert_after_index(List_info *list, int index, Data_node ins);
void delet_index(List_info *list, int index);
void insert_before_index(List_info *list, int index, Data_node ins);
int number_free_block(List_info *list);
void print_arr(List_info *list);





/*
Node* Node_create(Data_node x);
void list_push_head(List_info* l, Data_node x);
Data_node list_pop_head(List_info* l);
void list_push_tail(List_info* l, Data_node x);
Data_node list_pop_tail(List_info* l);

void delet_node_list(List_info* l, Node* node_del, Data_node del);
void delet_elem_list(List_info* l, Data_node del);

void insert_after_elem(List_info *l, Data_node ins, Data_node after);
void insert_after_node(List_info *l, Node* node_after, Data_node ins);
void insert_before_node(List_info *l, Node* node_before, Data_node ins);
void insert_before_elem(List_info *l, Data_node ins, Data_node before);

Node* found_elem(List_info* l, Data_node x);

void list_dump(List_info *l,FILE* output);

void list_destroy(List_info* l);

*/

#endif