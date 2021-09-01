#ifndef ODN_LIST_FUNC_H
#define ODN_LIST_FUNC_H
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
	unsigned int canary_2;
};

Node *root_ptr; // = NULL;
//net head-a, ужасно	

Node* list_create (Data_node x);
void list_add_before (Node* elem_list, Data_node x);
Node* get_last_ptr(Node* root_ptr);
void list_push(Node* root_ptr, Data_node x);
void delet_elem_list(Node* elem_list, Node* root_ptr);
void delete_last(Node* root_ptr);
void list_dump(Node* root_ptr, FILE* output);
Node* found_elem(Node* root_ptr, Data_node x);

#endif