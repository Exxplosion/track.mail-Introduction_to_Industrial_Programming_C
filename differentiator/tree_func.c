#include "tree_func.h"

void write_tree_in_txt(node* s, FILE* file)
{
	assert(file != NULL);
    //(if(proior ))//у кюр > род.
	fprintf(file, "(");

	if (s -> right != NULL)
		write_tree_in_txt(s -> right, file);

	switch (s->type_node)
	{
		case VAR:
		{
			fprintf(file, "%s", get_func(s->val));
			break;
		}
		case NUM:
		{
			fprintf(file, "%lg", s -> val);
            break;
		}
        default:
        {
            fprintf(file, "%s", get_func(s->val));
        }
	}

	if (s -> left != NULL)
		write_tree_in_txt(s -> left, file);

	fprintf(file, ")");
}



int found_var(node *s)
{
    static int flag = 0;

    if (s -> right != NULL)
        found_var(s -> right);

    if (s->type_node == VAR)
    {
        flag = 1;
    }

    if (s -> left != NULL)
        found_var(s -> left);

    return flag;
}

node* get_node(int type, val_t val, node* left, node* right)
{
  node* node_supp = (node*) calloc (1, sizeof(node));

  node_supp -> type_node = type;
  node_supp -> val = val;

  node_supp -> left = left;
  node_supp -> right = right;

  if (left) 
  	node_supp-> left -> parent = node_supp;
  if (right) 
  	node_supp -> right -> parent = node_supp;

  return node_supp;
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

node* copy_node(node* cur_node)
{
  node* node_supp = (node*) calloc(1, sizeof(node));

  node_supp -> type_node = cur_node -> type_node;
  node_supp -> val = cur_node -> val;

  node_supp -> left = NULL;
  node_supp -> right = NULL;

  if (cur_node -> left)
    node_supp -> left = copy_node(cur_node -> left);

  if (cur_node -> right)
    node_supp -> right = copy_node(cur_node -> right);

  return node_supp;
}

char* get_func(val_t value) 
{
    switch ((int) value)
    {
        case SUM:
            return "+";
        case SUB:
            return "-";
        case MUL:
            return "*";
        case DIV:
            return "/";
        case SIN:
            return "sin";
        case COS:
            return "cos";
        case LOG:
            return "ln";
        case TAN:
            return "tg";
        case COT:
            return "ctg";
        case SQRT:
            return "sqrt";
        case EXP:
            return "exp";
        case POW:
            return "^";
        case VAR_X:
            return "x";
        case VAR_Y:
            return "y";

        default:
            return "Unknown";
    }

}



void tree_print(tree* t, FILE* file)
{
	if (t == NULL)
	{
		err("tree not create");
		return;
	}
	fprintf (file, "digraph Tree\n{\n");

	int current_n = 1;
	supp_print (file, t -> root, 0, &current_n, NO);
	fprintf (file, "}");
}


void supp_print(FILE* out, node* cur, int parent, int* current_n, int side)
{
	//static int count = 0;
	//count++;
	const int current_n_cpy = *current_n;
	fprintf(out, "subgraph clust_%d{\n", *current_n);
	//block:

	if (cur->type_node == NUM)
	{
		fprintf(out, "\tval_%d [ shape = \"record\", label = \"{ %d\\n%p|{ %lg\\n } }\"]", *current_n, *current_n, cur, (cur -> val));
	}
	else // (cur->type_node == FUNC)
	{
		fprintf(out, "\tval_%d [ shape = \"record\", label = \"{ %d\\n%p|{ %s\\n } }\"] ", *current_n, *current_n, cur, get_func(cur -> val));
	}

	fprintf (out, "}\n\n");

	if (side == LEFT) //печатаем стрелки
	     fprintf (out, "\t\tval_%d:<center> -> val_%d [label=\"  \" color=\"#228b22\" fontcolor=\"#228b22\"];\n", parent, *current_n);
	if (side == RIGHT)
	     fprintf (out, "\t\tval_%d:<center> -> val_%d [label=\"  \" color=\"#228b22\" fontcolor=\"#228b22\"];\n", parent, *current_n);
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