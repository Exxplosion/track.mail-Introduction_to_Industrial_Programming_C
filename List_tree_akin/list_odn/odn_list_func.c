#include "odn_list_func.h"

Node* list_create(Data_node x)
{
	Node *out = NULL;

	if ((out = (Node *) malloc(sizeof(Node))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
	}
	
	out->next = NULL;
	out->val = x;
	return out;
}

void list_add_before(Node* elem_list, Data_node x)
{
	Node *supp = (Node *) malloc(sizeof(Node));
	supp->next = elem_list->next;
	supp = elem_list;
	Node *new_elem = list_create(x);
	elem_list->next = new_elem;
	new_elem->next = supp->next;
}

Node* get_last_ptr(Node* root_ptr)
{
	assert(root_ptr != NULL);

	Node *supp = root_ptr;
	while(supp->next)
	{
		supp = supp->next;
	}
	//printf("%p\n", supp);
	return supp;
}

void list_push(Node* root_ptr, Data_node x)
{
	assert(root_ptr != NULL);
	list_add_before(get_last_ptr(root_ptr), x);
}

void delet_elem_list(Node* elem_list, Node* root_ptr)
{
	assert(root_ptr != NULL);

	Node *supp = root_ptr;
	while (supp->next != elem_list)
	{
		supp = supp->next;
	}
	supp->next = elem_list->next;
	free(elem_list);
}

void delete_last(Node* root_ptr)
{
	assert(root_ptr != NULL);
	delet_elem_list(get_last_ptr(root_ptr), root_ptr);
}


void list_dump(Node* root_ptr,FILE* output)
{
	if(!root_ptr)
	{
		errno = LIST_UNDERFLOW;
		err("LIST_UNDERFLOW");
	}

	Node* supp = root_ptr;
	int i = 0;
	fprintf(output, "\t");
	while (supp)
	{
		fprintf(output, "\"Elem_list(%d) (ptr: %p), next_ptr = %p, Data: %d <-%p\"->", i++, supp, supp->next, supp->val, &supp->val);
		supp = supp->next;
	}
	fprintf(output, "NULL;\n");
}

void list_destroy(Node* root_ptr)
{
	Node *tmp = root_ptr;
	Node *supp = root_ptr;
	while (supp) 
	{
		tmp = supp->next;
		free(supp);
		supp = tmp;
	}
	root_ptr = NULL;
}


Node* found_elem(Node* root_ptr, Data_node x)
{
	assert(root_ptr != NULL);

	Node *supp = root_ptr;
	while (supp)
	{
		if (supp->val == x)
			return supp;
		supp = supp->next;
	}

	return NULL;
}