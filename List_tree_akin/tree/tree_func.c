#include "tree_func.h"

void create_head_tree(val_t val, tree *t) 
{

	node *tmp = NULL;
	if ((tmp = (node *) malloc(sizeof(node))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
	}

	tmp->left = tmp->right = NULL;
	tmp->val = val;
	tmp->parent = NULL;
	t->root = tmp;
	(t->size)++;
}

void write_tree_in_txt(node *s, FILE* file)
{
	assert(file != NULL);
	fprintf(file, "{");
	fprintf(file, "%s\n", s -> val);
	if (s -> left != NULL)
		write_tree_in_txt(s -> left, file);
	if (s -> right != NULL)
		write_tree_in_txt(s -> right, file);

	fprintf(file, "}\n");
}


node* formation_tree(tree *s, char* tree_txt, int* cur)
{
	if (tree_txt[*cur] != '{')
	{
		printf("File not tree, %d \n", *cur);
		exit(-1);
	}

	node* node_supp = (node*) malloc(sizeof(node));
	(*cur) = (*cur) + (sizeof(char));
	s -> size++;
	node_supp -> val = &tree_txt[*cur];

	while(!((tree_txt[*cur] == '{') || (tree_txt[*cur] == '}')))
	{
		(*cur)++;
	}

	tree_txt[*cur - 1] = '\0';

	if (tree_txt[*cur] == '{')
	{
		node_supp -> left = formation_tree(s, tree_txt, cur);
		node_supp -> left -> parent = node_supp;
		node_supp -> right = formation_tree(s, tree_txt, cur);
		node_supp -> right -> parent = node_supp;
	}

	if (tree_txt[*cur] !='}')
	{
		printf("File not tree, %d \n", *cur);
		exit(-1);
	}

	(*cur) = (*cur) + (2*sizeof(char)); //+'\n'

	return node_supp;
}




node* node_push_after(tree *t, int side, val_t val, node* node_after)
{
	if(t->root == NULL)
	{
		printf("tree not create, push in root %s", val);
		create_head_tree(val, t);
		return NULL;
	}

	if (side == LEFT)
	{
		node_after -> left = node_create(t, node_after, val);
		//(t->size)++;
		return node_after->left;
	}
	if (side == RIGHT)
	{
		node_after -> right = node_create(t, node_after, val);
		//(t->size)++;
		return node_after->right;
	}
}

node* node_create(tree* t, node* parent, val_t val)
{
	if (t == NULL)
	{
		err("tree not create");
		return NULL;
	}

	node* supp = (node*) malloc(sizeof(node));
	supp->val = val;
	supp->parent = parent;
	supp -> left = NULL;
	supp -> right = NULL;
	(t -> size)++;
	return supp;
}

node* node_delete(tree* t, node* node_del)
{
	if (node_del -> parent -> left == node_del) //удаляем левый или правый?
		free(node_del -> parent -> left);
		node_del -> parent -> left = NULL;
	if (node_del -> parent -> right == node_del)
		free(node_del -> parent -> right);
		node_del -> parent -> right = NULL;
	if (node_del -> left != NULL) //удаляем(?) узлы удаляемого узла
		node_delete(t, node_del -> left);
	if (node_del -> right != NULL)
		node_delete(t, node_del -> right);
	(t -> size)--;
	return node_del -> parent;
}

void print_tree(node* s)
{
	if (s == NULL)
	{
		err("tree not create");
		return;
	}
	printf("val_TREE /%s/ \n", s->val);
	print_tree(s->left);
	print_tree(s->right);
}


void tree_print(tree* t)
{
    FILE* out = fopen("dump.dot", "w");
	if (t == NULL)
	{
		err("tree not create");
		return;
	}
	fprintf (out, "digraph Tree\n{\n");

	fprintf(out, "\tsize [ label =\"size = %d\" shape=diamond, conditional=true];\n", t -> size);

	int current_n = 1;
	supp_print (out, t -> root, 0, &current_n, NO);
	fprintf (out, "}");
	fclose (out);
}


void supp_print(FILE* out, node* cur, int parent, int* current_n, int side)
{
	//static int count = 0;
	//count++;
	const int current_n_cpy = *current_n;
	fprintf(out, "subgraph clust_%d{\n", *current_n);
	//block:
	fprintf(out, "\tval_%d [ shape = \"record\", label = \"{ %d\\n%p|{ value = %s\\n ", *current_n, *current_n, cur, (cur -> val));
	fprintf(out, " |<parent> parent\\n%p } | { <left> left\\n%p | <right> right\\n%p } }\"]", cur -> parent , cur -> left, cur -> right); 
	fprintf (out, "}\n\n");
	if (side == LEFT) //печатаем стрелки
	     fprintf (out, "\t\tval_%d:<left> -> val_%d [label=\"  Yes \" color=\"#228b22\" fontcolor=\"#228b22\"];\n", parent, *current_n);
	if (side == RIGHT)
	     fprintf (out, "\t\tval_%d:<right> -> val_%d [label=\"  No \" color=\"#ff7e40\" fontcolor=\"#ff7e40\"];\n", parent, *current_n);
	if (cur->left)
	{
	    (*current_n)++;
	    supp_print(out, cur -> left, current_n_cpy, current_n, LEFT);
	}
	 if (cur->right)
	{
	    (*current_n)++;
	    supp_print(out, cur->right, current_n_cpy, current_n, RIGHT);
	}
	}