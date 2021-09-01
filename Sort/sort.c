#include "comparison.h"
#include "text_print.h"
#include <
.h>

const int SIZE_INCREMENT = 256;

int main()
{
	int lenght_аfile = 0;
	char *text = NULL;
	FILE *fp = NULL;
	fp = fopen("Textt.txt", "r");

	if (fp == NULL)
	{
		perror("Can't open file");
		return 1;
	}

	/* formation of source text in text[] */
	fseek(fp, 0, SEEK_END);

	if ((lenght_file = ftell(fp)) == -1L)
	{
		perror("ftell err");
		return -2;
	}

	fseek(fp, 0, SEEK_SET);

	text = (char *) calloc(lenght_file + 1, sizeof(char));

	if (text == NULL)
	{
		perror("nope memory");
		return  -1;	
	}

	while ((fread(text, sizeof(char), lenght_file, fp) != lenght_file))
	{
		;
	}

	fclose(fp);


	/* formation array pointers to start of lines text */
	lines *line = NULL;
	lines *supp = NULL; //промежуточный указатель
	int n = SIZE_INCREMENT; //initial size array
	line = (lines *) calloc(SIZE_INCREMENT, sizeof(lines));

	if (line == NULL)
	{
		perror("nope memory");
		return  -1;
	}

	char *s = text;
	char *s_next = strchr(s, '\n'); //next pointer after word

	int i = 0;
	line[i].len_line = s_next - s;
	line[i].lineptr = s;
	i++;
	s = s_next;
	s_next = strchr(s + 1, '\n');

	while (s_next != NULL)
	{
		line[i].len_line = s_next - s - 1;
		line[i].lineptr = s + 1;
		s = s_next;
		s_next = strchr(s+1, '\n'); 
		i++;
		if (i == n)
		{
			n += SIZE_INCREMENT;
			supp = (lines *) realloc(line, n * sizeof(lines));
			if (supp == NULL)
			{
				perror("nope memory");
				return  -1;
			}
			line = supp;
		}
	}

	line = (lines *) realloc(line, i * sizeof(lines));

	int m = i; //всего строк


	/* SORTING by symbols */
	qsort((void *) line, m, sizeof(lines), (int(*) (const void *, const void *)) mystrcmp);
	qsort((void *) line, m, sizeof(lines), (int(*) (const void *, const void *)) mystrcmp);

	fp = fopen("Textt_sorted_first.txt", "w");
	text_print(line, fp, m);
	fclose(fp);

	/* SORTING by last symbols */
	qsort((void *) line, m, sizeof(lines), (int(*) (const void *, const void *)) mystrcmp_last);

	fp = fopen("Textt_sorted_last.txt", "w");
	text_print(line, fp, m);
	fclose(fp);

	/* source text */
	n = lenght_file;
	fp = fopen("Textt_source.txt", "w");
	fprintf(fp, "%.*s (%d)\n", n, text, lenght_file);
	fclose(fp);

	free(text);
	//free(supp);
	free(line);  
	return 0;
}