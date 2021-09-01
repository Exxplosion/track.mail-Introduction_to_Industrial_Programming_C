#ifndef DV_LIST_FUNC_H
#define DV_LIST_FUNC_H
#define err(msg) fprintf(stderr, "in FILE %s; line %d; error %d: %s\n", __FILE__, __LINE__, errno, msg);


#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

enum ERROR_CODE
{
	Success,
	ZERO_SIZE, //0
	LIST_UNDERFLOW,
	LIST_BROKE, //3
	NOPE_MEM
};


typedef int Data_node;

typedef struct Node_t Node;

struct Node_t
{
	Data_node val;
	Node *next;
	Node *prev;
};

typedef struct List List_info;

struct List
{
	unsigned int size_list;
	Node *head_ptr;
	Node *tail_ptr;
};


List_info* list_create();
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

#endif