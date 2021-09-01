#include "dv_list_func.h"

List_info* list_create()
{
	List_info *out = NULL;

	if ((out = (List_info *) malloc(sizeof(List_info))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
	}

	out->head_ptr = NULL;
	out->tail_ptr = NULL;
	out->size_list = 0;
	return out;
}


Node* Node_create(Data_node x)
{
	Node *out = NULL;
	if ((out = (Node *) malloc(sizeof(Node))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
	}

	out->val = x;
	out->next = NULL;
	out->prev = NULL;
	return out;
}


void list_push_head(List_info* l, Data_node x)
{
	assert(l != NULL);
	Node* supp = Node_create(x);
	supp->next = l->head_ptr;
	supp->prev = NULL;

	if (l->head_ptr) //если был элемент
	{
		l->head_ptr->prev = supp; //прошлой голове кинуть prev на новую
	}
	else
	{
		l->tail_ptr = supp;
	}
	l->head_ptr = supp;
	l->size_list++;
}

Data_node list_pop_head(List_info* l)
{
	assert(l != NULL);
	if (l->head_ptr == NULL)
	{
		errno = LIST_UNDERFLOW;
		err("LIST_UNDERFLOW");
	}

	Node* supp = l->head_ptr;
	l->head_ptr = l->head_ptr->next;
	l->head_ptr->prev = NULL; //прошлой голове кинуть prev на null
	if (l->size_list == 1)
	{
		l->tail_ptr = NULL;
	}
	Data_node a = supp->val;
	free(supp);
	l->size_list--;
	return a;
}

void list_push_tail(List_info* l, Data_node x)
{
	assert(l != NULL);
	Node* supp = Node_create(x);
	supp->prev = l->tail_ptr;
	supp->next = NULL;

	if (l->tail_ptr) //если был элемент
	{
		l->tail_ptr->next = supp; //прошлой голове кинуть prev на новую
	}
	else
	{
		l->head_ptr = supp;
	}
	l->tail_ptr = supp;
	l->size_list++;
}

Data_node list_pop_tail(List_info* l)
{
	assert(l != NULL);
	if (l->tail_ptr == NULL)
	{
		errno = LIST_UNDERFLOW;
		err("LIST_UNDERFLOW");
		//return;
	}

	Node* supp = l->tail_ptr;
	l->tail_ptr = l->tail_ptr->prev;
	l->tail_ptr->next = NULL; //прошлой голове кинуть prev на null
	if (l->size_list == 1)
	{
		l->head_ptr = NULL;
	}
	Data_node a = supp->val;
	free(supp);
	l->size_list--;
	return a;
}

void insert_after_node(List_info *l, Node* node_after, Data_node ins) //dont work
{
	assert(node_after != NULL);
	Node *supp = Node_create(ins);

	if (node_after == l->tail_ptr)
	{
		list_push_tail(l, ins);
	}

	Node *supp_2 = Node_create(ins); //copy node_after 
    supp_2 -> next = node_after -> next;
    node_after -> next = supp;
    supp -> next = supp_2 -> next;
    supp -> prev = node_after;
    supp->next->prev = supp;
    free(supp_2);
    l->size_list++;
}

void insert_before_node(List_info *l, Node* node_before, Data_node ins) //dont work
{
	assert(node_before != NULL);
	Node *supp = Node_create(ins);

	if (node_before == l->head_ptr)
	{
		list_push_head(l, ins);
	}

	Node *supp_2 = Node_create(ins); //copy node_after 
    supp_2 -> prev = node_before -> prev;
    node_before -> prev = supp;
    supp -> prev = supp_2 -> prev;
    supp -> next = node_before;
    supp->prev->next = supp;
    free(supp_2);
    l->size_list++;
}

void insert_before_elem(List_info *l, Data_node ins, Data_node before) //dont work
{
	Node *node_before = found_elem(l, before);
	insert_before_node(l, node_before, ins);
}

void insert_after_elem(List_info *l, Data_node ins, Data_node after) //dont work
{
	Node *node_after = found_elem(l, after);
	insert_after_node(l, node_after, ins);
}


void delet_node_list(List_info* l, Node* node_del, Data_node del)
{
	assert(node_del != NULL);
	if(node_del == NULL)
	{
		return;
	}

	Node *supp = Node_create(del);
	supp = node_del;

	if (node_del == l->tail_ptr)
	{
		list_pop_tail(l);
		return;
	}

	if (node_del == l->head_ptr)
	{
		list_pop_head(l);
		return;
	}

	node_del->next->prev = node_del->prev;
	node_del->prev->next = supp->next;
	l->size_list--;
	free(node_del);
}

void delet_elem_list(List_info* l, Data_node del)
{
	Node *node_del = found_elem(l, del);
	delet_node_list(l, node_del, del);
}


void list_destroy(List_info* l)
{
	Node *supp = l->head_ptr;
	Node *tmp = l->head_ptr;

	while (supp) 
	{
		tmp = supp->next;
		free(supp);
		supp = tmp;
	}

	l->tail_ptr = NULL;
	l->head_ptr = NULL;
	l->size_list = 0;
}


Node* found_elem(List_info* l, Data_node x)
{
	assert(l != NULL);
	Node *supp = l->head_ptr;
	while (supp)
	{
		if (supp->val == x)
			return supp;
		supp = supp->next;
	}

	err("ELEM DON'T FOUND");

	return NULL;
}

void list_dump(List_info *l,FILE* output)
{
	if(!l->head_ptr)
	{
		errno = LIST_UNDERFLOW;
		err("LIST_UNDERFLOW");
	}

	Node* supp = l->head_ptr;
	int i = 0;
	fprintf(output, "digraph G{\n");
	fprintf(output, "\t");
	while (supp)
	{
		fprintf(output, "\"%d\" [shape=\"record\", label=\"Prev ptr: %p | Cur ptr: %p | Number elem: %d| Data: %d| Next_ptr: %p\"];\n", i, supp -> prev, supp, i, supp->val, supp->next);
		supp = supp->next;
		i++;
	}
	fprintf(output, "\"NULL_head\" -> \n");

	for (int j = 0; j <= i; j++)
	{
			fprintf(output, "%d ->", j);
	}
	fprintf(output, "NULL_tail;\n");
	fprintf(output, "}");
}