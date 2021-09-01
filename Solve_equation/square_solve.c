//--------------------------------------------------
//! Solves a square equation ax^2 + bx + c = 0;
//!
//! input a, b, c - coefficient (a != 0) 
//! Pointers x1, x2 - 1st and 2nd root
//! 
//! Output - x1,x2 - roots equation.
//!
//! Square_solve return number roots
//--------------------------------------------------

#include <stdio.h>
#include <assert.h> 
#include <math.h>
#include <ctype.h>

enum number_roots
{
	infinity_of_roots = -1,
	No_roots,
	One_root,
	Two_roots
};


int Linear_solve(double k, double c, double *x1)   //solve equation kx + c = 0
{
	if (k != 0)
	{
		*x1 = - c / k;
		return One_root;
	}
	else
	{
		if (c == 0)
		{
			return infinity_of_roots;
		}

		else //c != 0
		{
			return No_roots;
		}
		
	}
}

int Square_solve(double a, double b, double c, double *x1, double *x2)
{
	assert (x1 != NULL);
	assert (x2 != NULL);
	assert (x1 != x2);

	assert (isfinite(a));
	assert (isfinite(b));    
	assert (isfinite(c)); 

	if (a == 0)
	{
		*x1 = *x2;
		return Linear_solve(b, c, x1);
	}				//not square //KB: solve linear function

	if (b == 0)
	{
		if (c == 0)
		{
			*x2 = *x1 = 0;
			return One_root;
		}

		if (a*c > 0)
		{
			return No_roots;
		}
		
		if (a*c < 0)
		{
			*x1 = sqrt(-c/a);
			*x2 = -sqrt(-c/a);
			return Two_roots;
		}
	}

	if (c == 0)
	{
		*x1 = 0;
		*x2 = (-b)/a;  // a != 0
		return Two_roots;

	}

	double d = b*b - 4*a*c;

	if (d < 0)
	{
		return No_roots;
	}

	if (d == 0)
	{
		*x1 = *x2 = -b / (2*a);
		return One_root;
	}

	else
	{
		double sqrt_d = sqrt(d);
		
		*x1 = (-b - sqrt_d) / (2*a);
		*x2 = (-b + sqrt_d) / (2*a);
	}
		return Two_roots; 
}

int main()
{
	printf("enter a, b, c: ");

	double a = NAN, b = NAN, c = NAN;//KB: use NAN ; 

	int n = scanf ("%lg %lg %lg", &a, &b, &c);

	 while (n != 3)
	{
		while (getchar() != '\n');
		printf("need 3 arguments, u entered %d \n", n);  
		printf("enter a, b, c: ");
		//while (getchar() != '\n')
		n = scanf ("%lg %lg %lg", &a, &b, &c);
	}												

	 if ((a != a) || (b != b) || (c != c)) 
	 {
	 	return 2;
	 }
	 
	double x1 = 0, x2 = 0;

	switch (Square_solve(a, b, c, &x1, &x2)) //KB: use enums //Не понял как его здесь применить(
	{
		case No_roots: printf ("No roots\n");
			break;
		case One_root: printf("x = %lg\n", x1);
			break;
		case Two_roots: printf("x1 = %lg, x2 = %lg\n", x1, x2);
			break;
		case infinity_of_roots: printf("infinity of roots\n");
			break;
		default: printf ("error");
			 return 1;
	}

	return 0;
}






