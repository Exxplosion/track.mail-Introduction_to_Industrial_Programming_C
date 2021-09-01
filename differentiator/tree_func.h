#ifndef TREE_FUNC_H
#define TREE_FUNC_H
#define err(msg) fprintf(stderr, "in FILE %s; line %d; error %d: %s\n", __FILE__, __LINE__, errno, msg);

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "calc.h"

enum
{
	Success,
	ZERO_SIZE, //0
	TREE_UNDERFLOW,
	TREE_BROKE, //3
	NOPE_MEM
} ERROR_CODE;

enum side
{
    LEFT = 1,
    RIGHT,
    NO,
} side;

typedef double val_t;

typedef struct node_t node;

struct node_t
{
    val_t val;
    int type_node;
    node* parent;
    node* left;
    node* right;
};

typedef struct tree_t tree;

struct tree_t
{
    node* root;
    int size;
};

node* node_create(tree* t, node* parent, val_t val);
void supp_print(FILE* out, node* cur, int parent, int* current_n, int side);
void tree_print(tree* t, FILE* file);
void write_tree_in_txt(node *t, FILE* file);
node* get_node(int type, val_t val, node* left, node* right);
char* get_func(val_t value);
node* copy_node(node* cur_node);
int found_var(node *s);


#endif