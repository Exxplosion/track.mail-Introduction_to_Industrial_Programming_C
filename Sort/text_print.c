#include "text_print.h"
#include <stdio.h>
#include <stdlib.h>
//#include "comparison.h"

void text_print(lines *line, FILE *fp, int m)
{
	for (int i = 0; i < m; i++)
	{
		if (line[i].lineptr != NULL)
		{
			int n = line[i].len_line;
			fprintf(fp, "%.*s (%d)\n", n, line[i].lineptr, line[i].len_line);
		}
	}
}