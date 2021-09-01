#ifndef TREE_FUNC_H
#define TREE_FUNC_H
#define err(msg) fprintf(stderr, "in FILE %s; line %d; error %d: %s\n", __FILE__, __LINE__, errno, msg);

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>


extern enum
{
	Success,
	ZERO_SIZE, //0
	TREE_UNDERFLOW,
	TREE_BROKE, //3
	NOPE_MEM
} ERROR_CODE;


extern enum side
{
    LEFT = 1,
    RIGHT,
    NO,
} side;

typedef char* val_t;

typedef struct node_t node;

struct node_t
{
    val_t val;

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

void create_head_tree(val_t val, tree *t);
node* node_push_after(tree *t, int side, val_t val, node* node_after);
node* node_create(tree* t, node* parent, val_t val);
node* node_delete(tree* t, node* node_del);
void print_tree(node* s);
void supp_print(FILE* out, node* cur, int parent, int* current_n, int side);
void tree_print(tree* t);
node* formation_tree(tree *s, char* tree_txt, int* cur);
void write_tree_in_txt(node *t, FILE* file);




#endif