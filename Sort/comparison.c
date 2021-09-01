#include "comparison.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>


int mystrcmp(const lines *a, const lines *b) //в отличии от strcmp должен сравнивать не до '\0' 
{											 //а до '\n', или len_line
	assert(a != NULL);
	assert(b != NULL);	

	const lines *s = (const lines *) a; 
	const lines *t = (const lines *) b;
	int i = 0;
	int j = 0;


	while ((i+1 < s->len_line) && (j+1 < t->len_line))
	{
		if ((isalpha(s->lineptr[i])) == 0)
		{
			i++;
		} 

		if ((isalpha(t->lineptr[j])) == 0)
		{
			j++;
		} 

		if ((isalpha(s->lineptr[i])) && (isalpha(t->lineptr[j])))
		{
			return tolower(s->lineptr[i]) - tolower(t->lineptr[j]);
		}
	}
	return 0;
	/*for (i; (s->lineptr[i]) == (t->lineptr[i]); i++)		
	{
		if (i+1 == s->len_line)
		return 0;
	}	
	return (s->lineptr[i]) - (t->lineptr[i]);  */
}


int mystrcmp_last(const lines *a, const lines *b) //аналогична mystrcmp, сравнивает с последних символов 
{
	assert(a != NULL);
	assert(b != NULL);

	const lines *s = (const lines *) a; 
	const lines *t = (const lines *) b;

	int i = s->len_line - 1;
	int j = t->len_line - 1; 

	while ((i > 0) && (j > 0))
	{
		if ((isalpha(s->lineptr[i])) == 0)
		{
			i--;
		} 

		if ((isalpha(t->lineptr[j])) == 0)
		{
			j--;
		} 

		if ((isalpha(s->lineptr[i])) && (isalpha(t->lineptr[j])))
		{
			return tolower(s->lineptr[i]) - tolower(t->lineptr[j]);
		}
	}
	return 0;
}