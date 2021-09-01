#include "stack_func.h"

Stack* stack_create(int size)
{
	if (size <= 0)		
	{
		errno = ZERO_SIZE;
		err("ZERO_SIZE");
	}

	Stack *out = NULL;

	if ((out = (Stack *) malloc(sizeof(Stack))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
	}

	if ((out->a = (Data *) calloc(size, sizeof(Data))) == NULL)
	{
		errno = NOPE_MEM;
		err("NOPE_MEM");
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

void stack_push(Stack* s, Data x)
{
	stack_ASSERT(s);

	if (s->n == s->size)
	{
		(s->size) += SIZE_INCREMENT;
		Data *supp = s->a; //промежуточный указатель

		if ((supp = realloc(supp, (s->size) * sizeof(Data))) == NULL)
		{
			errno = STACK_OVERFLOW;
			err("STACK_OVERFLOW");
		}
		else
		{
			s->a = supp;
			poison_entry(s);

			s->a[s->n] = x;
			s->n++;

			s->hash = s->hash + x * (s->n-1);

			stack_ASSERT(s);
			errno = Success;
		}
	}
	else
	{
		s->a[s->n] = x;
		s->n++;

		s->hash = s->hash + x * (s->n-1);

		stack_ASSERT(s);
		errno = Success;		
	}
}

void poison_entry(Stack* s)
{
	for (int i = s->n; i < s->size; i++)
	{
		s->a[i] = POISON;
	}
}


Data stack_pop(Stack* s)
{
	stack_ASSERT(s);

	if (s->n > 0)
	{
		s->hash = s->hash - s->a[s->n-1] * (s->n-1);
		--s->n;
		errno = Success;
		return s->a[s->n];
	}

	errno = STACK_UNDERFLOW;
	err("STACK_UNDERFLOW");
}


Data stack_get(Stack* s)
{
	stack_ASSERT(s);

	if (s->n > 0)
	{
		//s->hash = s->hash - s->a[s->n-1] * (s->n-1);
		//--s->n;
		errno = Success;
		int m = s->n - 1;
		return s->a[m];
	}

	errno = STACK_UNDERFLOW;
	err("STACK_UNDERFLOW");
}


void stack_dump(Stack* s, int hash_2)
{
	printf("\n \n \n!!!!!!!!!STACK_DUMP_ACTIVATED!!!!!!!!!!! \n \n \n");

	if (s->n == 0)
	{
		errno = STACK_UNDERFLOW;
		err("STACK_UNDERFLOW");
	}

	for (int i = 0; i < s->n; i++)
	{
		printf("Data(%d) %d %p \n", i, s->a[i], &(s->a[i])); 
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


int stack_ASSERT(Stack *s)
{
	assert(s != NULL);

	int hash_2 = 0;

	for (int i = 0; i < s->n; i++)
	{
		hash_2 = hash_2 + i*s->a[i];  
	}

	//errno = Success;
	if (s->hash != hash_2)
	{
		stack_dump(s, hash_2);
		errno = STACK_BROKE;
		err("STACK_BROKE, hashes not equal");
	}


	if (s->canary_1 != canary_first)
	{
		stack_dump(s, hash_2);
		errno = STACK_BROKE;
		err("STACK_BROKE, canary_1 fallen");
	}

	if (s->canary_2 != canary_last)
	{
		stack_dump(s, hash_2);
		errno = STACK_BROKE;
		err("STACK_BROKE, canary_2 fallen");
	}
}