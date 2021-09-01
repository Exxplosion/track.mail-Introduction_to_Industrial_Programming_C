#ifndef DV_LIST_FUNC_H
#define DV_LIST_FUNC_H
#define err(msg) fprintf(stderr, "in FILE %s; line %d; error %d: %s\n", __FILE__, __LINE__, errno, msg);

#define canary_first  0xDED00BAD
#define canary_last  0xBABABEDA
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

extern enum
{
	Success,
	ZERO_SIZE, //0
	LIST_UNDERFLOW,
	LIST_BROKE, //3
	NOPE_MEM
} ERROR_CODE;


typedef int Data_node;

typedef struct Node_t Node;

struct Node_t
{
	unsigned int canary_1;
	Data_node val;
	Node *next;
	Node *prev;
	unsigned int canary_2;
};

typedef struct List List_info;

struct List
{
	unsigned int canary_1;
	unsigned int size_list;
	Node *head_ptr;
	Node *tail_ptr;
	unsigned int canary_2;
}


List_info* list_create();
Node* Node_create(Data_node x);
void list_push_head(List_info* l, Data_node x);
Data_node list_pop_head(List_info* l);
void list_push_tail(List_info* l, Data_node x);
Data_node list_pop_tail(List_info* l);
void Insert_after(List_info *l, Data_node ins, Data_node after);
void delet_elem_list(List_info* l, Data_node del);
void list_dump(List_info *l,FILE* output);
void list_destroy(List_info* l);
Node* found_elem(List_info* l, Data_node x);
#endif