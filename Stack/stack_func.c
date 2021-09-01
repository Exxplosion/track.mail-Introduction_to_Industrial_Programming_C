#include "stack_func.h"



Stack* stack_create(int size)
{
	if (size <= 0)		
	{
		errno = ZERO_SIZE;
		err("ZERO_SIZE");
		exit(ZERO_SIZE);// ZERO_SIZE;
	}

	Stack *out = NULL;

	if ((out = (Stack *) malloc(sizeof(Stack))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
		exit(NOPE_MEM);// NOPE_MEM;
	}	

	if ((out->a = (Data_t *) calloc(size, sizeof(Data_t))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
		exit(NOPE_MEM);// NOPE_MEM;
	}


	out->size = size;
	out->n = 0;


	out->canary_1 = canary_first;
	out->canary_2 = canary_last;

	out->hash = out->hash + out->size * (out->n) + out->n * (out->n+1);
	poison_entry(out);
	errno = Success;

	return out;
}


void poison_entry(Stack* s)
{
	assert(s!= NULL);
	for (int i = s->n; i < s->size; i++)
	{
		s->a[i] = POISON;
	}
}

int size_stack_get(Stack*s)
{
	(s->size) += SIZE_INCREMENT;
	Data_t *supp = s->a; //промежуточный указатель

	if ((supp = realloc(supp, (s->size) * sizeof(Data_t))) == NULL)
	{
		//errno = STACK_OVERFLOW;
		//err("STACK_OVERFLOW");
		return 0;
	}
	s->a = supp;
	return 1;
}

void stack_push(Stack* s, Data_t x)
{
	stack_OK(s);

	if (s->n == s->size)
	{
		//(s->size) += SIZE_INCREMENT;
		//Data_t *supp = s->a; //промежуточный указатель

		if (size_stack_get(s) == 0)
		{
			errno = STACK_OVERFLOW;
			err("STACK_OVERFLOW");
		}
		else
		{
			poison_entry(s);

			s->a[s->n] = x;
			s->n++;

			make_hash(s,x);

			stack_OK(s);
			errno = Success;
		}
	}
	else
	{
		s->a[s->n] = x;
		s->n++;

		make_hash(s, x);

		stack_OK(s);
		errno = Success;		
	}
}


void make_hash(Stack *s, Data_t x)
{
	s->hash = s->hash + x * (s->n-1);
}



Data_t stack_pop(Stack* s)
{
	stack_OK(s);

	if (s->n > 0)
	{
		make_hash_pop(s);
		--s->n;
		errno = Success;
		return s->a[s->n];
	}
	errno = STACK_UNDERFLOW;
	err("STACK_UNDERFLOW");
}


void make_hash_pop(Stack *s)
{
	s->hash = s->hash - s->a[s->n-1] * (s->n-1);
}


void stack_dump(Stack* s)
{
	assert(s != NULL);

	printf("\n \n \n!!!!!!!!!STACK_DUMP_ACTIVATED!!!!!!!!!!! \n \n \n");
	int hash_2 = hash_2_get(s);

	if (s->n == 0)
	{
		errno = STACK_UNDERFLOW;
		err("STACK_UNDERFLOW");
	}

	if (s->n < s->size && s->n > 0)
	{
		errno = STACK_BROKE;
		err("top stack falen");
		exit;// STACK_BROKE;
	}
	else
	{
		for (int i = 0; i < s->n; i++)
		{
			printf("Data_t(%d) %d %p \n", i, s->a[i], &(s->a[i])); 
		}
	}

	printf("size: %d, top: %d, hash: %ld, hash_2: %d, canary_1 %X, canary_2 %X \n" , s->size, s->n, s->hash, hash_2, s->canary_1, s->canary_2);
}

void stack_destroy(Stack* s)
{
	assert(s != NULL);
	s->hash = 0;
	s->size = 0;
	s->n = 0;
	free(s->a);
	s->a = NULL;
	free(s);
	errno = Success;
}


int hash_2_get(Stack *s)
{
	int hash_2 = 0;
	for (int i = 0; i < s->n; i++)
	{
		hash_2 = hash_2 + i*s->a[i];  
	}

	return hash_2;
}

int stack_OK(Stack *s)
{
	assert(s != NULL);

	int hash_2 = hash_2_get(s);


	//errno = Success;
	if (s->hash != hash_2)
	{
		//stack_dump(s, hash_2);
		//errno = STACK_BROKE;
		err("STACK_BROKE, hashes not equal");
		return STACK_BROKE;
	}


	if (s->canary_1 != canary_first)
	{
		//stack_dump(s, hash_2);
		//errno = STACK_BROKE;
		err("STACK_BROKE, canary_1 fallen");
		return STACK_BROKE;
	}

	if (s->canary_2 != canary_last)
	{
		//stack_dump(s, hash_2);
		//errno = STACK_BROKE;
		err("STACK_BROKE, canary_2 fallen");
		return STACK_BROKE;
	}

	if (s->n < s->size && s->n > 0)
	{
		//printf("top stack falen");
		errno = STACK_BROKE;
		err("top stack falen");
		return STACK_BROKE;
	}
}