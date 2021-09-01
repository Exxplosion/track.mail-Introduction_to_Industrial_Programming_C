#include "stack_func.h"
#include <ctype.h>



int main()
{
	Stack* s = stack_create(100);
	int m;
	int c;
	c = getchar();
	stack_push(s, c-'0');
	while ((c = getchar()) != (EOF)) 
		{
			if (isdigit(c))
			{
				stack_push(s, c-'0');
			}
			if ((char)(c) == '+')
			{
				m = stack_pop(s) + stack_pop(s);
				stack_push(s, m);
			}
			if ((char)(c) == '-')
			{
				m = stack_pop(s);
				m = stack_pop(s) - m;
				stack_push(s, m);
			}
			if ((char)(c) == '*')
			{
				m = stack_pop(s)*stack_pop(s);
				stack_push(s, m);
			}
		}
		printf("%d", stack_pop(s));
}